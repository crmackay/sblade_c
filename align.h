#ifndef align_H
#define align_H

#include "seq.h"


// direction elements allowed during alignment matrix creation and traversal
typedef enum {
	DIAG_MATCH,			// diagonal move because of a MATCH
	DIAG_MISMATCH,		// diagonal move because of a mismatch
	DIAG_N,				// diagonal move because of the query string has an "N"
	INS_I,				// insertion in the "i" direction
	INS_J,				// insertion in the "j" direction
	EDGE_I,				// the edge of the matrix in the i direction
	EDGE_J,				// the edge of the matrix in the j direction
	ORIGIN
} matrix_move;

// the alignment_matrices struct holds pointers to each of the four matrices accosiated with each
//		input sequence and its alignment to the contaiminant of interest
typedef struct alignment_matrices{
	double 	*H;			// H points to the log odds matrix
	int 	*D;			// D points to the direction matrix
	double 	*SL;		// SL points to the P(S|L) matrix
	double 	*SLP;		// SLP points to the P(S|L') matrix
} alignment_matrices;

// the alignment struct contains all the elements of a input read and its alignment
//		this includes, the input sequence, the input sequence's quality scores, the
//		subject (contaimenant) against which the input sequence is being aligned, and
//		a pointer to each of the 4 alignment matrices
typedef struct alignment{
	alignment_matrices *matrices; 	// M is the group of alignments associated with the two sequences
    seq	query;		// the query of the alignment
    seq	subject;	// the subject of the alignment
	seq	quals;		// quals for the query sequence
} alignment;

alignment *new_alignment(seq* query, seq* subj, seq* quals);


double probSLMatch(char s, char q, char q_qual);

double probSLMismatch(char s, char q, char q_qual);

double probSLMatch(char s, char q, char q_qual);

matrix_move match(char s, char q);

double phredToProbIncorrect(char p);

int max_match(double values[3]);

// creates and populates the matrices in the already allocated align_mat
int fill_matrices(alignment *input, alignment_matrices align_mat);

char *traceback(alignment *input, int max_i, int max_j);

#endif
