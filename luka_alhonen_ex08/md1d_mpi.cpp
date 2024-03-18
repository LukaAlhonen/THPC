//
// 1D molecular dynamics simulation code for course
// MATR326 Tools for high performance computing
// Antti Kuronen, University of Helsinki
//
// Try e.g.
// ./a.out 10000 0.001 100000 1 100 0
//


#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <numeric>
#include <mpi.h>

#define d  1.0
#define k1 1.0
#define k2 0.1
#define xsc 2.35

using namespace std;

ofstream fcoord;
string coord_file="coords.dat";

// --------------------------------------------------------------------------------------

void accel(int nat, int i, double *u, double *a, double box, vector<double>& x) 
{
	// Calculate the potential energy u 
	// and acceleration a of atom i.
	// Need to figure out how to get funky with carthesian shiet here
	int j,k;
	double dxl,dxr;
		
	j=i-1; if (j<0) j=nat-1;
	k=i+1; if (k>=nat) k=0;

	dxl=x[i]-x[j];
	dxr=x[k]-x[i];
	if (dxl<-box/2.0) dxl+=box;
	if (dxl>=box/2.0) dxl-=box;
	if (dxr<-box/2.0) dxr+=box;
	if (dxr>=box/2.0) dxr-=box;
	dxl-=d;
	dxr-=d;

	*u=(k1*(dxl*dxl+dxr*dxr)+k2*(dxl*dxl*dxl+dxr*dxr*dxr))/2.0;
	*a=-(2.0*k1*(dxl-dxr)+3.0*k2*(dxl*dxl-dxr*dxr));
}

// --------------------------------------------------------------------------------------

void printcoords(int nat, int n, vector<double> x, vector<double> ep, double box)
{
	int i;
	fcoord<<nat<<endl;
	fcoord<<"Frame number "<<n<<" "<<n<<" fs boxsize "<<box<<endl;
	for (i=0;i<nat;i++) fcoord<<"Fe "<<xsc*x[i]<<" "<<0<<" "<<0<<" "<<ep[i]<<endl;
}

// --------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	// init mpi
	int rc, world_size, world_rank;
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		cerr << "MPI init failed!" << endl;
		return 1;
	}
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Create 1-D carthesian topology
	const int ndims = 1;
    int dims[ndims] = {0};
	int periods[ndims] = {1};
    int coords[ndims];
    int source, dest, dir = 0, shift, tag = 0;
	int reorder = 1;
	double msg_s, msg_r; // Send and receive buffers
	MPI_Status status;
	MPI_Comm comm;

	MPI_Dims_create(world_size, ndims, dims);
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm);

	vector<double> x;      // atom positions
	vector<double> v;      //      velocities
	vector<double> v0;     //      previous veloocities (leap frog needs them)
	vector<double> a;      //      accelerations
	vector<double> ep;     //      potential energies
	vector<double> ek;     //      kinetic energies

	double epsum,eksum;    // system energies
	double dt;             // time step 
	double vsc;            // mean initial velocity
	double box;            // system size
	int nat;               // number of atoms
	int maxt;              // number of time steps simulated
	int eout;              // energy output interval
	int coout;             // coordinate output interval (lot of data, beware!)
	int start, end;
	int i,n;
	double vsum,vave,rn;

	// Root process reads args
	if (world_rank == 0) {
		// Get number of atoms, time step and simulation length from command line
		if (argc<5 || argc>7) {
			cerr << "usage: "<< argv[0] << " nat dt maxt vsc [eout [coout]]\n";
			cerr << "    nat   = number of atoms\n";
			cerr << "    dt    = time step\n";
			cerr << "    maxt  = number of time steps in simulation\n";
			cerr << "    vsc   = mean velocity of atoms in the beginning ('temperature')\n";
			cerr << "    eout  = interval for printing energies to stdout\n";
			cerr << "    coout = interval for printing coordinates to '" << coord_file << "'\n";
			return(128);
		}

		coout=0;
		eout=1;
		nat=atoi(*++argv);
		int atoms_per_process = nat / world_size;
		int remainder = nat % world_size;

		for (int k = 0; k < world_size; k++) {
			int start = k * atoms_per_process;
			int end = start + atoms_per_process;

			// If this is the last process, add the remainder
			if (k == world_size - 1) {
				end += remainder;
			}

			// Send the start and end indices to process i
			if (k != 0) { // No need to send to ourselves
				MPI_Send(&start, 1, MPI_INT, k, 0, MPI_COMM_WORLD);
				MPI_Send(&end, 1, MPI_INT, k, 0, MPI_COMM_WORLD);
			}
		}
		start = 0;
		end = 25;
		// Divide number of atoms between processes
		nat = atoms_per_process;
		dt=atof(*++argv);
		maxt=atoi(*++argv);
		vsc=atof(*++argv);

		if (argc>5) eout=atoi(*++argv);
		if (argc>6) coout=atoi(*++argv);
	} else {
		MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	cerr << "Process " << world_rank << " has start: " << start << " and end: " << end << endl;

	// Distribute args to all processes	
	MPI_Bcast(&nat, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&dt, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&maxt, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&vsc, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&eout, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&coout, 1, MPI_INT, 0, MPI_COMM_WORLD);

	x=vector<double>(nat);
	v=vector<double>(nat);
	v0=vector<double>(nat);
	a=vector<double>(nat);
	ep=vector<double>(nat);
	ek=vector<double>(nat);

	// Initialize atoms positions and give them random velocities
	box=nat;
	srand(time(NULL));
	for (i=start;i<end;i++) {
		x[i%nat]=i;
		rn=(double)rand()/RAND_MAX;
		v[i%nat]=vsc*(rn-0.5); // Scale the velocities to vsc*[-½,½]
	}

	if (coout>0) fcoord.open(coord_file);

	// Remove center of mass velocity
	// NOTE: Commented out in order to make the exercise easier
	// vsum=accumulate(v.begin(),v.end(),0.0);
	// vsum/=nat;
	// for (i=0;i<nat;i++) v[i]-=vsum;

	n=0;

	// If the user wants calculate initial energy and print initial coords
	if (coout>0) {
	for (i=0;i<nat;i++) accel(nat,i,&ep[i],&a[i],box,x);
		printcoords(nat,n,x,ep,box);
	}


	// Simulation proper

	auto t0=std::chrono::system_clock::now();

	for (n=0;n<maxt;n++) {
		for (i=0;i<nat;i++) v0[i]=v[i];

		for (i=0;i<nat;i++)
			// New potential energy and acceleration
			accel(nat,i,&ep[i],&a[i],box,x);

		for (i=0;i<nat;i++) {
			// Leap frog integration algorithm: update position and velocity
			v[i]=v[i]+dt*a[i];
			x[i]=x[i]+dt*v[i];
			// Check periodic boundary conditions
			// Need to do get funky with cart_shift and sendrecv here
			// Since sendrecv is blocking, this will cause a chain where all atoms at the boundaries are shifed appropriately
			if (x[i] < start) {
				// If x[i] is less than the left boundary we get a coordinate from the process to the left
				msg_s = x[i];
				cerr << "Process " << world_rank << " is sending message: " << msg_s << endl;
				MPI_Cart_shift(comm, dir, 1, &source, &dest);
				MPI_Sendrecv(&msg_s, 1, MPI_DOUBLE, dest, tag, &msg_r, 1, MPI_DOUBLE, source, tag, comm, &status);
				cerr << "Process " << world_rank << " received msg: " << msg_r << endl;
				x[i] = msg_r;
			}
			if (x[nat-1] >= end) {
				// If x[nat-1] (the rightmost atom) is greater than the right boundary we send its' coordinate to the process on the right
				msg_s = x[nat-1]; if (world_rank == world_size-1) msg_s 
				cerr << "Process " << world_rank << " is sending message: " << msg_s << endl;
				MPI_Cart_shift(comm, dir, -1, &source, &dest);
				MPI_Sendrecv(&msg_s, 1, MPI_DOUBLE, dest, tag, &msg_r, 1, MPI_DOUBLE, source, tag, comm, &status);
				cerr << "Process " << world_rank << " received msg: " << msg_r << endl;
				x[nat-1] = msg_r;
			}

			// if (x[i]<0.0 ) x[i]=x[i]+box;
			// if (x[i]>=box) x[i]=x[i]-box;

			// Calculate kinetic energy (note: mass=1)
			vave=(v0[i]+v[i])/2.0;
			ek[i]=1.0/2.0*vave*vave;
		}

		// Buffers for MPI_Reduce
		double tot_epsum, tot_eksum;

		// Calculate and print total potential end kinetic energies
		// and their sum (= total energy that should be conserved).
		epsum=accumulate(ep.begin(),ep.end(),0.0);
		eksum=accumulate(ek.begin(),ek.end(),0.0);

		// Need to call MPI_Reduce with MPI_SUM here before printing
		// May have to rethink using the default comuunicator??
		MPI_Reduce(&eksum, &tot_eksum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&epsum, &tot_epsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		// Only root processes prints
		if (world_rank == 0) {
			if (eout>0)
				if (n%eout==0)
			printf("%20.10g %20.10g %20.10g %20.10g\n",dt*n,epsum+eksum,epsum,eksum);
			if (coout>0) 
				if (n%coout==0)
					printcoords(nat,n,x,ep,box);
		}
	}

	auto t1=std::chrono::system_clock::now();
	auto wct=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
	cerr<<"Wall clock time: "<<wct.count()/1000.0<<" seconds\n";

	if (coout>0) fcoord.close();
	rc = MPI_Finalize();
	if (rc != MPI_SUCCESS) {
		cerr << "MPI finalize failed!" << endl;
		return 1;
	}
	return 0;
}

