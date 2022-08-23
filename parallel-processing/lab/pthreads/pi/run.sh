#!/usr/local/bin/bash

echo "- MPI Monte Carlo Pi -"

echo -n "# of Processes: "
read PROC

echo -n "# of RandomPts: "
read RAND

mpiexec -n $PROC ./pi $RAND
