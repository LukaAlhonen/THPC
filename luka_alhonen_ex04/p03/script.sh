#! /bin/sh

n=100

executable_1=p03_1_O0
executable_2=p03_1_O3
executable_3=p03_2_O0
executable_4=p03_2_O3
executable_5=p03_4_O0
executable_6=p03_4_O3
executable_7=p03_8_O0
executable_8=p03_8_O3
executable_9=p03_16_O0
executable_10=p03_16_O3
executable_11=p03_32_O0
executable_12=p03_32_O3

outdir="out"
if [ ! -d "${outdir}" ]; then
    mkdir -p "${outdir}"
fi

output_1="${outdir}/${executable_1}_output.txt"
output_2="${outdir}/${executable_2}_output.txt"
output_3="${outdir}/${executable_3}_output.txt"
output_4="${outdir}/${executable_4}_output.txt"
output_5="${outdir}/${executable_5}_output.txt"
output_6="${outdir}/${executable_6}_output.txt"
output_7="${outdir}/${executable_7}_output.txt"
output_8="${outdir}/${executable_8}_output.txt"
output_9="${outdir}/${executable_9}_output.txt"
output_10="${outdir}/${executable_10}_output.txt"
output_11="${outdir}/${executable_11}_output.txt"
output_12="${outdir}/${executable_12}_output.txt"

# Clean up and init
python3 unroll.py
rm -f $output_1 $output_2 $output_3 $output_4 $output_5 $output_6 $output_7 $output_8 $output_9 $output_10 $output_11 $output_12
make clean; make

for (( i=1; i<=n; i++ ))
do
    echo "Iteration ${i}"
    ./$executable_1 >> $output_1
    ./$executable_2 >> $output_2
    ./$executable_3 >> $output_3
    ./$executable_4 >> $output_4
    ./$executable_5 >> $output_5
    ./$executable_6 >> $output_6
    ./$executable_7 >> $output_7
    ./$executable_8 >> $output_8
    ./$executable_9 >> $output_9
    ./$executable_10 >> $output_10
    ./$executable_11 >> $output_11
    ./$executable_12 >> $output_12
done

echo "Done"
echo "Calculating averages ..."

python3 medians.py $output_1 $output_2 $output_3 $output_4 $output_5 $output_6 $output_7 $output_8 $output_9 $output_10 $output_11 $output_12