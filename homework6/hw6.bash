#!/bin/bash

#PBS -N hw6_test
#PBS -l walltime=1:00:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark
./homework6 TestImage.png and_mask.png testEx true 75 16

# Don't forget to change job name appropirately (for convenience) when
# you uncomment the following command to measure performance of if

# /usr/bin/time -v ./Exercise4 if
# /usr/bin/time -v ./Exercise4 if
# /usr/bin/time -v ./Exercise4 if

#end of script
