#include <mpi.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include <iostream>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::vector<float> data;
    std::vector<int> sendcounts(world_size);
    std::vector<int> recvcounts(world_size), displs(world_size);
    // Code goes here

    // Process 0
    int recvcount;
    if (world_rank == 0) {
        // Read data from file into data vector
        std::fstream file("ex7p3.dat");
        float val;

        std::cout << "Reading data points from \"ex7p3.dat\" into vector..." << std::endl;
        if (argc == 2) {
            int n_data;
            int i = 0;
            try {
                int n_data = std::stoi(argv[1]);
                std::cout << "Number of data points to be read: " << n_data << std::endl;
                while (i < n_data && file >> val) {
                    data.push_back(val);
                    i++;
                }
            } catch (std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
            } catch (std::out_of_range& e) {
                std::cerr << "Argument out of range: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Number of data points not specified, reading the whole file." << std::endl; 
            while (file >> val) {
                data.push_back(val);
            }
        }
        file.close();

        std::cout << "Done." << std::endl;

        // Divide data among other processes
        // for (int i = 0; i < world_size; i++) {
        //     sendcounts[i] = data.size() / world_size;
        //     displs[i] = i * sendcounts[i];
        // }
        // recvcount = data.size() / world_size;
        int base_count = data.size() / world_size;
        int remainder = data.size() % world_size;
        
        for (int i = 0; i < world_size; i++) {
            // Each process gets a base count
            sendcounts[i] = base_count;
            // The first 'remainder' processes get an extra element
            if (i < remainder) {
                sendcounts[i]++;
            }
            // Calculate displacements
            recvcounts[i] = base_count + (i < remainder ? 1 : 0);
            displs[i] = i == 0 ? 0 : displs[i-1] + sendcounts[i-1];
        }
    }

    MPI_Bcast(recvcounts.data(), world_size, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<float> recvdata(recvcounts[world_rank]);
    MPI_Scatterv(data.data(), sendcounts.data(), displs.data(), MPI_FLOAT, recvdata.data(), recvcounts[world_rank], MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "Process " << world_rank << " received " << recvdata.size() << " points of data\n" <<std::flush; 

    float sum = 0, sq_sum = 0;
    for (float val : recvdata) {
        sum += val;
        sq_sum += val * val;
    }

    std::cout << "Process " << world_rank << " sum: " << sum << ", var: " << sq_sum << "\n" << std::flush;

    std::vector<float> sums(world_size), sq_sums(world_size);
    MPI_Gather(&sum, 1, MPI_FLOAT, sums.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Gather(&sq_sum, 1, MPI_FLOAT, sq_sums.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD);

    if (world_rank == 0) {
        float total_sum = std::accumulate(sums.begin(), sums.end(), 0.0f);
        float total_sq_sum = std::accumulate(sq_sums.begin(), sq_sums.end(), 0.0f);
        float avg = total_sum / data.size();
        float variance = (total_sq_sum / data.size()) - (avg * avg);
        std::cout << "Average: " << avg << ", Variance: " << variance << "\n" << std::flush;
    }

    MPI_Finalize();
}