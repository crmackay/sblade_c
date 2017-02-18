// take a pointer to an alignment struct, and run traceback and prob tests until no more

#include "align.h"


// takes an alignment input and two piece of memory for the final read and
// searches the aligment matrices for contaminantion alignments, until no more
// are found, and places the trimmed sequence and its cooresponding quality string
// into the supplied memory blocks
// returns zero means no error was encountered
int trim(alignment *input, char *out_seq[100], char *out_quals[100]){

    // find best alignment position
    // check probabilities in SL and SLP
    // if a contamination:
        // follow traceback to find 5' terminus

    // repeat above until check is false of 5' terminus is 0

    return(0);
};
