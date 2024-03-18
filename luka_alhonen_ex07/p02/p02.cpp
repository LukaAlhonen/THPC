#include <mpi.h>
#include <iostream>
#include <random>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::mt19937 gen(world_rank); 
    std::uniform_real_distribution<> distrib(0, 1);

    long int total_points_per_process = 10000000; // Total number of points per process
    int points_within_unit_circle = 0; // Number of points within unit circle

    for (int i = 0; i < total_points_per_process; ++i) {
        double x = distrib(gen);
        double y = distrib(gen);
        double func_y = std::sqrt(1 - x * x); // Calculate y value using the function y = sqrt(1 - x^2)
        if (y <= func_y) {
            ++points_within_unit_circle;
        }
    }

    int total_points_within_unit_circle;
    MPI_Reduce(&points_within_unit_circle, &total_points_within_unit_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double pi_estimate = 4.0 * total_points_within_unit_circle / (total_points_per_process * world_size);
        std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;
    }

    MPI_Finalize();
}