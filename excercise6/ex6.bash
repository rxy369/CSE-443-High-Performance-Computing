#!/bin/bash

#PBS -N ex6_O3_profilers
#PBS -l walltime=0:30:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark once in each configuration
perf stat ./ex6 switch 250000000
perf stat ./ex6 if     250000000

# Collect callgrind data in each configuration
valgrind --tool=callgrind ./ex6 switch 250000000
valgrind --tool=callgrind ./ex6 if     250000000

#end of script
