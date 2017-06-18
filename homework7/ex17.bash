#!/bin/bash
# Lines beginning with # are comments
# Only lines beginning #PBS are processed by qsub
#PBS -N hw7
#PBS -l walltime=00:05:00
#PBS -l nodes=3:ppn=1
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR

mpiexec -n $PBS_NP ./homework7 numbers_100.txt

#end of script
