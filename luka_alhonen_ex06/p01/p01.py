from os import environ
environ['OMP_NUM_THREADS'] = '1'
from scipy.linalg import eig
import numpy as np
import time
import matplotlib.pyplot as plt

def compute_eigen(a) -> float:
    start = time.process_time()
    eig(a)
    end = time.process_time()
    return end - start

def fill_matrix(n) -> np.ndarray:
    min_val = 1
    max_val = n**2
    log_space = np.geomspace(min_val, max_val, num=n**2)
    
    # Reshape the array to a square matrix
    log_space = log_space.reshape(n, n)
    
    return log_space

def compute_cpu_times() -> dict:
    sizes = np.arange(30, 1001)
    durations = {}
    iterations = 20 # number of times eigen values are calculated

    # init matrices
    print('Initializing matrices ...\n')
    for n in sizes:
        print(f'Filling matrix of size {n}x{n} ...\n')
        a = fill_matrix(n)
        sum = 0.0
        print(f'Computing eigen values for {n}x{n}, {iterations} times:')
        for i in range(iterations):
            sum += compute_eigen(a)
        avg_duration = sum / iterations
        print(f'Average CPU time for {n}x{n} matrix: {avg_duration}\n')
        durations[n] = avg_duration

    return durations

def plot_durations(durations) -> None:
    # Extract matrix sizes and CPU times
    matrix_sizes = list(durations.keys())
    cpu_times = list(durations.values())

    # Create the plot
    plt.plot(matrix_sizes, cpu_times)

    # Label the axes and give the plot a title
    plt.xlabel('Matrix Size')
    plt.ylabel('Average CPU Time')
    plt.title('CPU Time as a Function of Matrix Size')

    # save plot to png
    plt.savefig('cputimes.png')

def main() -> None:
    durations = compute_cpu_times()
    print(durations)
    plot_durations(durations)

if __name__ == '__main__':
    main()
