#!/bin/bash

#PBS -N ex8_matSum
#PBS -l walltime=0:30:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

# Run the benchmark 5 times in each configuration
echo "--------------[ columnSum_colMajor version stats ]-----------------"
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum colMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum colMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum colMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum colMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum colMajor

echo "--------------[ columnSum_rowMajor version stats ]-----------------"
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum rowMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum rowMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum rowMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum rowMajor
perf stat -e cache-references,cache-misses,branches,branch-misses ./MatrixColumnSum rowMajor

#end of script

