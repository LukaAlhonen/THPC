#! /bin/sh

n=100

executable_1="p01_a"
executable_2="p01_a_optimised"
executable_3="p01_b"
executable_4="p01_b_optimised"

output_1="${executable_1}_output.txt"
output_2="${executable_2}_output.txt"
output_3="${executable_3}_output.txt"
output_4="${executable_4}_output.txt"

# Cleanup before running

rm -rf $output_1 $output_2 $output_3 $output_4
make clean; make

for (( i=1; i<=$n; i++ ))
do
    ./$executable_1 >> $output_1
    ./$executable_2 >> $output_2
    ./$executable_3 >> $output_3
    ./$executable_4 >> $output_4
done

python3 medians.py $output_1 $output_2 $output_3 $output_4
