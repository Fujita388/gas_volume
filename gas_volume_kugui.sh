#!/bin/sh

#PBS -q F16cpu
#PBS -l select=16:ncpus=128:mpiprocs=128:ompthreads=1
#PBS -l walltime=01:00:00
#PBS -N g_v_with_surf01

module load intel intel-mpi
mpiexec -n 2048 ./a.out > gas_volume.log 2>&1
