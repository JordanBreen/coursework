#!/usr/local/bin/bash
#####################
# name:
#   jacobi.main()
# parameters:
#   argv[0]: char[] source_filename - the name of the program.
#   argv[1]: int    num_threads     - the number of threads.
#   argv[2]: int    grid_size       - the length and width of the grid (excluding the boundary).
#   argv[3]: int    max_iter        - the maximum amount of jocobi iterations before ending calculations, base case A.
#   argv[4]: double error_tolerance - the minimum amount of change between each grid cell per iteration, base case B.
#   argv[5]: char[] output_filename - the file that the output is directed to, formatted to be read and plotted by GNUplot.
# returns: (int)
#   0 - normal termination
#   1 - abnormal termination
DATA_DIR="./results/dat/"
DATA_EXT="dat"
TEXT_DIR="./results/txt/"
IMAG_EXT="png"
IMAG_DIR="./results/img/"
TEXT_EXT="txt"
SIZEGRID=512
STRTPROC=2
LASTPROC=32
MAX_ITER=30000
ERR_TOLR=0.001
for ((p=$STRTPROC; $p <= $LASTPROC; p*=2))
do
    export DATA_DEST="${DATA_DIR}P${p}_S${SIZEGRID}.${DATA_EXT}"
    export IMAG_DEST="${IMAG_DIR}P${p}_S${SIZEGRID}.${IMAG_EXT}"
    export PLOT_NAME="Solution[P${p}_S${SIZEGRID}]"

    TEXT_DEST="${TEXT_DIR}P${p}_S${SIZEGRID}.${TEXT_EXT}"

    echo -n > $DATA_DEST
    echo -n > $IMAG_DEST
    echo -n > $TEXT_DEST
    
    ./jacobi $p $SIZEGRID $MAX_ITER $ERR_TOLR $DATA_DEST #> "${TEXT_DEST}"
    
    ./run_gnuplot.sh
 
    export -n DATA_DEST
    export -n IMAG_DEST
    export -n PLOT_NAME
done
