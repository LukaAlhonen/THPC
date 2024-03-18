!
! 1D molecular dynamics simulation code for course
! MATR326 Tools for high performance computing
! Antti Kuronen, University of Helsinki
!
! Try e.g.
! ./a.out 10000 0.001 100000 1 100 0
!

module sizes
  integer,parameter :: rk0=selected_real_kind(5,10)    ! single precision
  integer,parameter :: rk=selected_real_kind(10,40)    ! double precision
  integer,parameter :: rk2=selected_real_kind(30,200)  ! quadruple precision
  integer,parameter :: MAXBUF=200
end module sizes

! --------------------------------------------------------------------------------------

program md1d
  use sizes
  implicit none  

  real(rk),allocatable :: x(:)   ! atom positions
  real(rk),allocatable :: v(:)   !      velocities
  real(rk),allocatable :: v0(:)  !      previous veloocities (leap frog needs them)
  real(rk),allocatable :: a(:)   !      accelerations
  real(rk),allocatable :: ep(:)  !      potential energies
  real(rk),allocatable :: ek(:)  !      kinetic energies

  real(rk) :: epsum,eksum        ! system energies

  real(rk) :: dt                 ! time step 
  real(rk) :: vsc                ! mean initial velocity
  real(rk) :: box                ! system size
  integer :: nat                 ! number of atoms
  integer :: maxt                ! number of time steps simulated
  integer :: eout                ! energy output interval
  integer :: cout                ! coordinate output interval (lot of data, beware!)

  integer :: t0,t1,wct,rate
  
  integer :: i,n,ia
  character(len=MAXBUF) :: arg

  ! Get number of atoms, time step and simulation length from command line
  
  ia=command_argument_count()
  if (ia<4.or.ia>6) then
     call get_command_argument(0,arg)
     write(6,'(a,a,a)')   'usage: ',trim(arg),' nat dt maxt vsc [eout [cout]]'
     write(6,'(a)')       '    nat  = number of atoms'
     write(6,'(a)')       '    dt   = time step'
     write(6,'(a)')       '    maxt = number of time steps in simulation'
     write(6,'(a)')       '    vsc  = mean velocity of atoms in the beginning (''temperature'')'
     write(6,'(a)')       '    eout = interval for printing energies to stdout'
     write(6,'(a)')       '    cout = interval for printing coordinates to ''fort.10'''
     stop
  end if
  cout=0
  eout=1
  call get_command_argument(1,arg); read(arg,*) nat
  call get_command_argument(2,arg); read(arg,*) dt
  call get_command_argument(3,arg); read(arg,*) maxt
  call get_command_argument(4,arg); read(arg,*) vsc
  if (ia>4) then
     call get_command_argument(5,arg); read(arg,*) eout
  end if
  if (ia>5) then
     call get_command_argument(6,arg); read(arg,*) cout
  end if

  allocate(x(nat),v(nat),v0(nat),a(nat),ep(nat),ek(nat))

  ! Initialize atoms positions and give them random velocities
  
  box=nat
  x=[(real(i,rk),i=0,nat-1)]
  call random_number(v)
  v=vsc*(v-0.5) ! Scale the velocities to vsc*[-½,½]

  ! Remove center of mass velocity
  ! NOTE: Commented out in order to make the exercise easier
  !v=(v-sum(v)/nat)

  ! If the user wants calculate initial energy and print initial coords
  
  if (cout>0) then
     do i=1,nat
        call accel(i,ep(i),a(i))
     end do
     n=0
     call printcoords()
  end if


  ! Simulation proper

  call system_clock(count_rate=rate)
  call system_clock(count=t0)
  
  time_loop: do n=1,maxt

     v0=v

     atom_loop1: do i=1,nat
        ! New potential energy and acceleration
        call accel(i,ep(i),a(i))
     end do atom_loop1
     
     atom_loop2: do i=1,nat
        ! Leap frog integration algorithm: update position and velocity
        v(i)=v(i)+dt*a(i)
        x(i)=x(i)+dt*v(i)
        ! Check periodic boundary conditions
        if (x(i)<0.0 ) x(i)=x(i)+box
        if (x(i)>=box) x(i)=x(i)-box
        ! Calculate kinetic energy (note: mass=1)
        ek(i)=1.0/2.0*((v0(i)+v(i))/2.0)**2
     end do atom_loop2

     ! Calculate and print total potential end kinetic energies
     ! and their sum that should be conserved.
     epsum=sum(ep)
     eksum=sum(ek)
     if (eout>0) then
        if (mod(n,eout)==0) print '(4g20.10)',dt*n,epsum+eksum,epsum,eksum
     end if
     if (cout>0) then
        if (mod(n,cout)==0) call printcoords()
     end if
     
  end do time_loop
  
  call system_clock(count=t1)
  write(0,'(a,g16.8,a)') 'Wall clock time: ',real(t1-t0,rk)/rate,' seconds'
  
  stop

  contains

    ! --------------------------------------------------------------------------------------

    subroutine accel(i,u,a)
      ! Calculate the potential energy u 
      ! and acceleration a of atom i.
      integer,intent(in) :: i
      real(rk),intent(out) :: u,a
      real(rk),parameter :: d=1.0,k1=1.0,k2=0.1
      integer :: j,k
      real(rk) :: dxl,dxr
      
      j=i-1; if (j<1) j=nat
      k=i+1; if (k>nat) k=1

      dxl=x(i)-x(j)
      dxr=x(k)-x(i)
      if (dxl<-box/2.0) dxl=dxl+box
      if (dxl>=box/2.0) dxl=dxl-box
      if (dxr<-box/2.0) dxr=dxr+box
      if (dxr>=box/2.0) dxr=dxr-box
      dxl=dxl-d;
      dxr=dxr-d;

      u=(k1*(dxl**2+dxr**2)+k2*(dxl**3+dxr**3))/2.0
      a=-(2.0*k1*(dxl-dxr)+3.0*k2*(dxl**2-dxr**2))

      return
    end subroutine accel

    ! --------------------------------------------------------------------------------------
    
    subroutine printcoords()
      integer :: ia
      real(rk),parameter :: xsc=2.35
      write(10,*) nat
      write(10,'(a,x,i0,x,i0,x,a,3f14.4)') 'Frame number ',n,n,' fs boxsize',box,10.0,10.0
      do ia=1,nat
         write(10,'(a,x,4g20.10)') 'Fe',xsc*x(ia),0.0,0.0,ep(ia)
      end do
      return
    end subroutine printcoords
      
  end program md1d
