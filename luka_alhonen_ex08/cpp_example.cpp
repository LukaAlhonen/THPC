#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int myid, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    const int ndims = 1;
    int dims[ndims] = {0};
    int periods[ndims] = {1};
    int coords[ndims];
    int source, dest, dir = 0, shift, tag = 0;
    bool reorder = true;
    char msg_s = 'a' + myid;
    char msg_r;
    MPI_Status status;

    MPI_Comm comm;
    MPI_Dims_create(nprocs, ndims, dims);
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm);
    MPI_Cart_coords(comm, myid, ndims, coords);

    for (shift = -1; shift <= 1; shift += 2) {
        MPI_Cart_shift(comm, dir, shift, &source, &dest);
        MPI_Sendrecv(&msg_s, 1, MPI_CHAR, dest, tag, &msg_r, 1, MPI_CHAR, source, tag, comm, &status);
        std::cout << "sh " << shift << " id " << myid << " msg_r " << msg_r << " src " << source << " dest " << dest << std::endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (myid == nprocs-1) std::cerr << "I am " << myid << std::endl;
    MPI_Finalize();
    return 0;
}