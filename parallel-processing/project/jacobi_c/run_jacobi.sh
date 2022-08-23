#!/bin/sh
#run 3 instances of jacobi
./jacobi 10 10 0.001 solution_a.dat > results.txt
./jacobi 100 100 0.001 solution_b.dat >> results.txt
./jacobi 1000 1000 0.000001 solution_c.dat >> results.txt
