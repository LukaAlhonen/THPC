#! /bin/sh

n=100

executable_1=p01_formatted_O0
executable_2=p01_formatted_O3
executable_3=p01_unformatted_O0
executable_4=p01_unformatted_O3
outdir="data"
if [ ! -d "${outdir}" ]; then
	mkdir -p "${outdir}"
fi

output_1="${outdir}/${executable_1}_output.txt"
output_2="${outdir}/${executable_2}_output.txt"
output_3="${outdir}/${executable_3}_output.txt"
output_4="${outdir}/${executable_4}_output.txt"

# Cleanup before running
rm -f $output_1 $output_2 $output_3 $output_4
make clean; make

# Run programs n times
echo "Executing ${n} iterations ${executable_1}, ${executable_2}, ${executable_3} and ${executable_4}"

for (( i=1; i<n; i++ ))
do
	echo "Iteration ${i}"
	./$executable_1 >> $output_1
	./$executable_2 >> $output_2
	./$executable_3 >> $output_3
	./$executable_4 >> $output_4
done

echo "Done."
echo "Calculating averages ..."
./medians $output_1 $output_2 $output_3 $output_4
echo "Done."