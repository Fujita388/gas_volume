#!/bin/sh

#PBS -q i2cpu
#PBS -l select=2:ncpus=128:mpiprocs=128:ompthreads=1
#PBS -l walltime=00:30:00
#PBS -N gas_volume

module load intel intel-mpi
mpiexec -n 128 ./a.out > gas_volume.log 2>&1
