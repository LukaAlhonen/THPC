#! /bin/sh

n=100

executable_1="p02_O0"
executable_2="p02_O3"

out1="${executable_1}_a.txt"
out2="${executable_1}_b.txt"
out3="${executable_1}_c.txt"
out4="${executable_2}_a.txt"
out5="${executable_2}_b.txt"
out6="${executable_2}_c.txt"

make clean; make

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