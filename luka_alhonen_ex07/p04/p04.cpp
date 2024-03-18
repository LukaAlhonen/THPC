#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if ((world_size & (world_size - 1)) != 0 && world_size > 0) {
        if (world_rank == 0) {
            std::cerr << "The number of processes must be a power of two." << std::endl;
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int sum = world_rank;
    for (int stride = 1; stride < world_size; stride *= 2) {
        if ((world_rank / stride) % 2 == 0 && world_rank + stride < world_size) {
            int receivedValue;
            MPI_Recv(&receivedValue, 1, MPI_INT, world_rank + stride, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += receivedValue;
        } else if ((world_rank / stride) % 2 == 1 && world_rank - stride >=0 ) {
            MPI_Send(&sum ,1 ,MPI_INT ,world_rank - stride ,0 ,MPI_COMM_WORLD);
            break; 
        }
    }

    if (world_rank == 0) {
        std::cout << "The total sum is: " << sum << std::endl;
    }

    MPI_Finalize();
}
