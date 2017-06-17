#!/bin/bash

#PBS -N ex7_unroll
#PBS -l walltime=0:30:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark 5 times in each configuration
echo "---------------------[ standard version stats ]---------------------"
perf stat ./unroll standard
perf stat ./unroll standard
perf stat ./unroll standard
perf stat ./unroll standard
perf stat ./unroll standard

echo "---------------------[ unrolled version stats ]---------------------"
perf stat ./unroll unrolled
perf stat ./unroll unrolled
perf stat ./unroll unrolled
perf stat ./unroll unrolled
perf stat ./unroll unrolled

#end of script
