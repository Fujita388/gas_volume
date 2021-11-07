#!/bin/sh
#PBS -M naofuji.1220@gmail.com
#PBS -m ae
#PBS -l nodes=1:ppn=3

cd $PBS_O_WORKDIR
hostname
mpirun -np 3 ./cps/cps para.sh
