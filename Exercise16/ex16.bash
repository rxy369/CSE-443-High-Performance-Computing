#!/bin/bash
# Lines beginning with # are comments
# Only lines beginning #PBS are processed by qsub
#PBS -N exercise16
#PBS -l walltime=00:05:00
#PBS -l mem=1GB
#PBS -l nodes=2:ppn=1
#PBS -S /bin/bash

# We intentionally don't combine error and output streams to make
# testing a bit easier.

cd $PBS_O_WORKDIR
/usr/bin/time -v mpiexec -n $PBS_NP ./Exercise16 numbers.txt

#end of script

