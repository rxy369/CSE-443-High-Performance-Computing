#!/bin/bash

# Lines beginning with # are comments Only lines beginning #PBS are
# processed by qsub

#PBS -N factor_count8
#PBS -l walltime=00:10:00
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR

# Set number of OpenMP threads based on number of cores specified as
# part of PBS job.
export OMP_NUM_THREADS=$PBS_NP

# Run the program 3 times to get measure consistent timings
/usr/bin/time -v ./exercise10
/usr/bin/time -v ./exercise10
/usr/bin/time -v ./exercise10

#end of script
