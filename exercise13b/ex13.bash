#!/bin/bash

# Lines beginning with # are comments Only lines beginning #PBS are
# processed by qsub

#PBS -N ex13
#PBS -l walltime=00:15:00
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR

# Setup the actual scheduling strategy to be used for OpenMP-for
# export OMP_SCHEDULE="static"
export OMP_SCHEDULE="dynamic"

# Set number of OpenMP threads based on number of cores specified as
# part of PBS job.
export OMP_NUM_THREADS=$PBS_NP

# Print configuration information to ease tracking in output files
echo "Schedule being used: $OMP_SCHEDULE"
echo "Number of threads being used: $OMP_NUM_THREADS"

# Run the program 3 times to get measure consistent timings
/usr/bin/time -v ./exercise13 10000
/usr/bin/time -v ./exercise13 10000
/usr/bin/time -v ./exercise13 10000

#end of script

