!
! Example of MPI cartesian topology in 1D and
! using MPI_Sendrecv to pass data along the chain
! in both directions.
!
!
!   ----------    msg_r    ----------    msg_s   ----------
!   | source |  ------->   |  myid  |  ------->  |  dest  |
!   ----------             ----------            ----------
!
! Compilation and run (to get neat output):
!    mpif90 mpi_topo1_sendrecv.f90
!    mpirun -np 4 ./a.out | sort -gk2
!

program mpi_topo_sendrecv
  use mpi
  implicit none
  integer,parameter :: ndims=1
  integer :: rc,myid,nprocs,comm,dims(ndims),status(mpi_status_size)
  integer :: coords(ndims),source,dest,dir,shift,tag=0
  logical :: periodic(ndims),reorder=.true.
  character(len=1) :: msg_r,msg_s
  integer :: ac=ichar('a')
  character(len=80) :: fmt

  call mpi_init(rc)
  call mpi_comm_rank(mpi_comm_world,myid,rc)
  call mpi_comm_size(mpi_comm_world,nprocs,rc)
  msg_s=char(ac+myid)

  periodic=.true.
  dims=0
  call mpi_dims_create(nprocs,ndims,dims,rc)
  call mpi_cart_create(mpi_comm_world,ndims,dims,periodic,reorder,comm,rc)
  call mpi_cart_coords(comm,myid,ndims,coords,rc)
  dir=0
  fmt='(2(a,x,i2,x),2x,a,x,a1,2x,2(x,a,x,i2))'
  
  do shift=-1,1,2
     call mpi_cart_shift(comm,dir,shift,source,dest,rc)
     call mpi_sendrecv(msg_s,1,mpi_character,dest,tag, &
                     & msg_r,1,mpi_character,source,tag, &
                     & comm,status,rc)
     print fmt,'sh',shift,'id',myid,'msg_r',msg_r,'src',source,'dest',dest
  end do

  call mpi_finalize(rc)
end program mpi_topo_sendrecv
