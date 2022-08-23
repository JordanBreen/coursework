#!/bin/bash
#----------------------------------------------------
# Sample Slurm job script
#   for TACC Stampede2 KNL nodes
#
#   *** MPI Job on Normal Queue ***
#
# Last revised: 14 Sep 2020
#
# Notes:
#
#   -- Launch this script by executing
#      "sbatch knl.mpi.slurm" on Stampede2 login node.
#
#   -- Use ibrun to launch MPI codes on TACC systems.
#      Do not use mpirun or mpiexec.
#
#   -- Max recommended MPI tasks per KNL node: 64-68
#      (start small, increase gradually).
#
#   -- If you're running out of memory, try running
#      on more nodes using fewer tasks and/or threads
#      per node to give each task access to more memory.
#
#   -- Don't worry about task layout.  By default, ibrun
#      will provide proper affinity and pinning.
#
#   -- You should always run out of $SCRATCH.  Your input
#      files, output files, and exectuable should be
#      in the $SCRATCH directory hierarchy.
#
#
#----------------------------------------------------

#SBATCH -J hellotest       # Job name
#SBATCH -o hellotest.o%j   # Name of stdout output file
#SBATCH -e hellotest.e%j   # Name of stderr error file
#SBATCH -p normal          # Queue (partition) name
#SBATCH -N 4               # Total # of nodes
#SBATCH -n 512             # Total # of mpi tasks
#SBATCH -t 00:05:00        # Run time (hh:mm:ss)
#SBATCH --mail-user=jm23bree@siena.edu
#SBATCH --mail-type=all    # Send email at begin and end of job

# Other commands must follow all #SBATCH directives...

module list
pwd
date

# You should always run out of $SCRATCH.  Your input
#      files, output files, and exectuable should be
#      in the $SCRATCH directory hierarchy.
# Change directories to your $SCRATCH directory where your executable is

cd $SCRATCH

# Launch MPI code...

ibrun ./mpihello         # Use ibrun instead of mpirun or mpiexec

# ---------------------------------------------------
login2.stampede2(197)$
