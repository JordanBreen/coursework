#!/bin/sh
# expected arguments for palindrome()...
# argv[0] -> (str) program name (auto)
# argv[1] -> (int) maximum word length in dictionary, determined by shell script run.sh
# argv[2] -> (int) number of words in dictionary, determined by shell script run.sh
# argv[3] -> (str) filepath to dictionary
# argv[4] -> (str) filepath to output
# argv[5] -> (int) test number
# argv[6] -> (int) number of processes

DICT_FILE_NAME='/usr/share/dict/words'
OUT_FILE_NAME='./results.txt'
MAX_WORD_LEN="$(awk '{if(length($1)>max)max=length($0)}END{print max}' ${DICT_FILE_NAME})"
WORD_COUNT="$(wc -w ${DICT_FILE_NAME} | grep -Eo '[0-9]{1,}')"
NUM_TESTS=3
NUM_PROCS=6
PROCS='1 2 4 8 16 26'
echo -n > $OUT_FILE_NAME
for n in $(seq $NUM_TESTS)
do
    for p in $PROCS
    do
	./palindrome $MAX_WORD_LEN $WORD_COUNT $DICT_FILE_NAME $OUT_FILE_NAME $n $p
    done
done
./process_results $OUT_FILE_NAME $NUM_PROCS $NUM_TESTS 
