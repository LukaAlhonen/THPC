#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            std::cout << "This program requires exactly 2 processes." << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    int num_iterations = 1000;
    int max_message_size = 10000000000;
    std::vector<char> buffer(max_message_size);

    for (int message_size = 10000; message_size <= max_message_size; message_size *= 10) {
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();

        for (int i = 0; i < num_iterations; ++i) {
            if (rank == 0) {
                MPI_Send(buffer.data(), message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer.data(), message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (rank == 1) {
                MPI_Recv(buffer.data(), message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(buffer.data(), message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
        double end_time = MPI_Wtime();

        if (rank == 0) {
            double time_taken = end_time - start_time;
            double latency = time_taken / (2 * num_iterations);
            double bandwidth = (message_size * num_iterations) / (time_taken * 1e6);
            std::cout << "Message size: " << message_size << ", Latency: " << latency << ", Bandwidth: " << bandwidth << " MB/s" << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}