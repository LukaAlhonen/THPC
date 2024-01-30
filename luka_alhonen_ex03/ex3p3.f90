program ex3p3
  implicit none
  integer,parameter :: N=15000,NPRINT=500
  integer :: a(N,N)
  integer :: i,j

  ! Begin measurement
  do j=1,N
     do i=1,N
        a(i,j)=(i+j)/2
     end do
  end do
  ! End measurement

  print '(10i8)',a(1:N:NPRINT,1:N:NPRINT)

end program ex3p3

