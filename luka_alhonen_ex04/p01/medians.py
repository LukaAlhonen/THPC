import numpy as np
import sys

for file in sys.argv[1:]:
    with open(file, "r") as a_out:
        lines = a_out.readlines()
        values = np.array([float(line.strip()) for line in lines])
        print(f'Average of {file.replace("_output.txt", "")}: {values.mean()} s')