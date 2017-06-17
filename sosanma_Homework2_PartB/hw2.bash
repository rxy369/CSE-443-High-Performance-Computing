#!/bin/bash

#PBS -N hw2_tests
#PBS -l walltime=0:30:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark once in each configuration
perf stat ./sosanma_Homework2_PartB lambda
perf stat ./sosanma_Homework2_PartB inline

# Collect callgrind data in each configuration
valgrind --tool=callgrind ./sosanma_Homework2_PartB lambda
valgrind --tool=callgrind ./sosanma_Homework2_PartB inline

#end of script
