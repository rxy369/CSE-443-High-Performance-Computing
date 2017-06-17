#!/bin/bash
# Lines beginning with # are comments
# Only lines beginning #PBS are processed by qsub
#PBS -N exercise17
#PBS -l walltime=00:05:00
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR

echo "100000000 100000000 100000000 100000000 100000000 0" | /usr/bin/time -v mpiexec -n $PBS_NP ./Exercise17
echo "100000000 100000000 100000000 100000000 100000000 0" | /usr/bin/time -v mpiexec -n $PBS_NP ./Exercise17
echo "100000000 100000000 100000000 100000000 100000000 0" | /usr/bin/time -v mpiexec -n $PBS_NP ./Exercise17

#end of script
