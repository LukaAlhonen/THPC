#! /bin/sh

n=100

bin_a=omit_frame_pointer_a
bin_b=omit_frame_pointer_b
bin_c=omit_frame_pointer_c
bin_d=omit_frame_pointer_d
bin_e=omit_frame_pointer_e
bin_f=omit_frame_pointer_f

outdir="data"
if [ ! -d "${outdir}" ]; then
	mkdir -p "${outdir}"
fi
out_a="${outdir}/${bin_a}_output.txt"
out_b="${outdir}/${bin_b}_output.txt"
out_c="${outdir}/${bin_c}_output.txt"
out_d="${outdir}/${bin_d}_output.txt"
out_e="${outdir}/${bin_e}_output.txt"
out_f="${outdir}/${bin_f}_output.txt"

make clean; make
rm -f $out_a $out_b $out_c $out_d $out_e $out_f

echo "Executing ${n} iterations ${bin_a}, ${bin_b}, ${bin_c}, ${bin_d}, ${bin_e} and ${bin_f}"
for (( i=1; i<n; i++ ))
do
    echo "Iteration ${i}"
    ./$bin_a >> $out_a
    ./$bin_b >> $out_b
    ./$bin_c >> $out_c
    ./$bin_d >> $out_d
    ./$bin_e >> $out_e
    ./$bin_f >> $out_f
done
echo "Done."
echo "Calculating averages ..."
python3 medians.py $out_a $out_b $out_c $out_d $out_e $out_f
echo "Done."