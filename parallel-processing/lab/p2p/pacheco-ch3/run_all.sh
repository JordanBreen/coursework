#!/usr/local/bin/bash
mpicc -o mpi_hello mpi_hello.c
mpicc -o mpi_trap1 mpi_trap1.c
#mpicc -o mpi_trap2 mpi_trap2.c

mpiexec -n  8 ./mpi_hello > hello_8.txt
mpiexec -n 16 ./mpi_hello > hello_16.txt

mpiexec -n  8 ./mpi_trap1 > trap1_8.txt
mpiexec -n 16 ./mpi_trap1 > trap1_16.txt

#mpiexec -n  2 ./mpi_trap2 > trap2_2.txt
#mpiexec -n  4 ./mpi_trap2 > trap2_4.txt
#mpiexec -n  8 ./mpi_trap2 > trap2_8.txt
#mpiexec -n 16 ./mpi_trap2 > trap2_16.txt
#mpiexec -n 32 ./mpi_trap2 > trap2_32.txt
#mpiexec -n 64 ./mpi_trap2 > trap2_64.txt
