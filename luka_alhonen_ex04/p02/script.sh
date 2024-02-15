#! /bin/sh

n=50

executable_1="p02_O0"
executable_2="p02_O3"

out1="${executable_1}_a_output.txt"
out2="${executable_1}_b_output.txt"
out3="${executable_1}_c_output.txt"
out4="${executable_2}_a_output.txt"
out5="${executable_2}_b_output.txt"
out6="${executable_2}_c_output.txt"

# Clean up
make clean; make
rm -rf $out1 $out2 $out3 $out4 $out5 $out6

echo "Running p02_O0, p02_O3"

for (( i=1; i<=$n; i++ ))
do
    ./$executable_1 >> $out1
    ./$executable_1 "b" >> $out2
    ./$executable_1 "c" >> $out3
    ./$executable_2 >> $out4
    ./$executable_2 "b" >> $out5
    ./$executable_2 "c" >> $out6
done