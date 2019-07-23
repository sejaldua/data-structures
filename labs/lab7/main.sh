#!/usr/bin/env bash

mkdir $1


filename="/output"

for ((a=1; a <= $2; a++))
do
	echo $a > $1$filename$a".out"
done


dir="output"
mkdir $dir

input_path="input/input1.txt"
output_path="output/output1.txt"
ref_path="ref/ref1.txt"
cat $input_path | ./studentSub > $output_path
diff $output_path $ref_path