import numpy as np
import sys

for file in sys.argv[1:]:
    total_time = 0.0
    count = 0
    with open(file, "r") as a_out:
        for line in a_out:
            words = line.split()
            cpu_time = float(words[1])
            total_time += cpu_time
            count += 1
        
        print(f'Average of {file.replace("_output.txt", "")}: {total_time / count} s')