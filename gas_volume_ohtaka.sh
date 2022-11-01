#!/bin/bash

#SBATCH -p i8cpu
#SBATCH -N 8
#SBATCH -n 128
#SBATCH -c 8
#SBATCH -t 00:30:00

source /home/issp/materiapps/intel/lammps/lammpsvars.sh

srun ./a.out
