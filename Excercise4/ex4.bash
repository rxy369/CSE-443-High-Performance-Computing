#!/bin/bash

#PBS -N ex4_if_O2
#PBS -l walltime=0:10:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark
/usr/bin/time -v ./Excercise4 if
/usr/bin/time -v ./Excercise4 if
/usr/bin/time -v ./Excercise4 if

# Don't forget to change job name appropirately (for convenience) when
# you uncomment the following command to measure performance of if

# /usr/bin/time -v ./Exercise4 if
# /usr/bin/time -v ./Exercise4 if
# /usr/bin/time -v ./Exercise4 if

#end of script
