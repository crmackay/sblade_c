#ifndef align_H
#define align_H

#include <stdlib.h>

#include "seq.h"


typedef struct int_matrix
{
	int num_cols;
	int num_rows;
	int *loc;
} int_matrix;

typedef struct dbl_matrix
{
	int num_cols;
	int num_rows;
	double *loc;
} dbl_matrix;

int_matrix new_int_matrix(int len_x, int len_y);

// pos_x and pos_y are 0-based coordinates
int set_int_matrix_value(int_matrix M, int pos_x, int pos_y, int val);

int get_int_matrix_value(int_matrix M, int pos_x, int pos_y);

int destroy_int_matrix(int_matrix M);

dbl_matrix new_dbl_matrix(int len_x, int len_y);

// pos_x and pos_y are 0-based coordinates
int set_dbl_matrix_value(dbl_matrix M, int pos_x, int pos_y, double val);

double get_dbl_matrix_value(dbl_matrix M, int pos_x, int pos_y);

int destroy_dbl_matrix(dbl_matrix M);


// the alignment_matrices struct holds pointers to each of the four matrices accosiated with each
//		input sequence and its alignment to the contaiminant of interest
typedef struct alignment_matrices
{
	double 	*H;			// H points to the log odds matrix
	int 	*D;			// D points to the direction matrix
	double 	*SL;		// SL points to the P(S|L) matrix
	double 	*SLP;		// SLP points to the P(S|L') matrix
} alignment_matrices;

// the alignment struct contains all the elements of a input read and its alignment
//		this includes, the input sequence, the input sequence's quality scores, the
//		subject (contaimenant) against which the input sequence is being aligned, and
//		a pointer to each of the 4 alignment matrices
typedef struct alignment
{
	alignment_matrices *matrices; 	// M is the group of alignments associated with the two sequences
    seq	query;						// the query of the alignment
    seq	subject;					// the subject of the alignment
	seq	quals;						// quals for the query sequence
} alignment;

alignment *new_alignment(seq* query, seq* subj, seq* quals);

// direction elements allowed during alignment matrix creation and traversal
typedef enum
{
	DIAG_MATCH,			// diagonal move because of a MATCH
	DIAG_MISMATCH,		// diagonal move because of a mismatch
	DIAG_N,				// diagonal move because of the query string has an "N"
	INS_I,				// insertion in the "i" direction
	INS_J,				// insertion in the "j" direction
	EDGE_I,				// the edge of the matrix in the i direction
	EDGE_J,				// the edge of the matrix in the j direction
	ORIGIN
} matrix_move;

// calculates P(S|L)_k
double probSLMatch(char s, char q, char q_qual);

// calculates P(S|L')_k
double probSLMismatch(char s, char q, char q_qual);

// compares chars and determine which DIAG_xxx move to return
matrix_move match(char s, char q);

// utility function which takes an encoded PHRED score and return prob
// 	of a misscall
double phredToProbIncorrect(char p);

// take the values from each possible matrix move as an array, and returns
// 	the index of the highest one
int max_match(double values[3]);

// creates and populates the matrices in the already allocated align_mat
int fill_matrices(alignment *input, alignment_matrices align_mat);

//
char *traceback(alignment *input, int max_i, int max_j);




#endif
