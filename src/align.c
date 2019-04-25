#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "seq.h"
#include "align.h"


/**********************************************************
 int matrix
 ***********************************************************/
int_matrix* new_int_matrix(int num_cols, int num_rows)
{
	int_matrix* my_new_matrix = malloc(sizeof(int_matrix));
	if (my_new_matrix == NULL){return(NULL);}
	my_new_matrix->num_cols = num_cols;
	my_new_matrix->num_rows = num_rows;
	my_new_matrix->loc = (int*) malloc(sizeof(int) * (num_cols) * (num_rows));
	if (my_new_matrix->loc==NULL){return(NULL);}
	return(my_new_matrix);
}

// pos_x and pos_y are 0-based coordinates
int set_int_matrix_val(int_matrix* M, int pos_x, int pos_y, int val)
{
	// TODO-safety: add bounds checking somehow
	M->loc[(M->num_cols * pos_y) + pos_x] = val;
	return(0);
}

int get_int_matrix_val(int_matrix* M, int pos_x, int pos_y)
{
	// TODO-safety: add bounds checking somehow
	return M->loc[(M->num_cols * pos_y) + pos_x];
}

int destroy_int_matrix(int_matrix* M)
{
	free(M->loc);
	free(M);
	return(0);
}

int print_int_matrix(int_matrix* M)
{
	int err = 0;
	for (int i = 0; i<M->num_rows; i++)
	{
		for (int j = 0; j<M->num_cols; j++)
		{
			err = printf("%i ", get_int_matrix_val(M, j, i));
		}
		err = printf("\n");
	}
	err = printf("\n");
	return err;
}

/**********************************************************
 double matrix
 ***********************************************************/

dbl_matrix* new_dbl_matrix(int num_cols, int num_rows)
{
	dbl_matrix* my_new_matrix = malloc(sizeof(dbl_matrix));
	if (my_new_matrix == NULL){return(NULL);}
	my_new_matrix->num_cols = num_cols;
	my_new_matrix->num_rows = num_rows;
	my_new_matrix->loc = (double*) malloc(sizeof(double) * (num_cols) * (num_rows));
	if (my_new_matrix->loc == NULL){return(NULL);}
	return(my_new_matrix);
}

// pos_x and pos_y are 0-based coordinates
int set_dbl_matrix_val(dbl_matrix* M, int pos_x, int pos_y, double val)
{

	M->loc[(M->num_cols * pos_y) + pos_x] = val;
	return(0);
}

double get_dbl_matrix_val(dbl_matrix* M, int pos_x, int pos_y)
{
	return M->loc[(M->num_cols * pos_y) + pos_x];
}

int destroy_dbl_matrix(dbl_matrix* M)
{
	free(M->loc);
	free(M);
	return(0);
}

int print_dbl_matrix(dbl_matrix* M)
{
	int err = 0;
	for (int i = 0; i<M->num_rows; i++)
	{
		for (int j = 0; j<M->num_cols; j++)
		{
			err = printf("%2.2e ", get_dbl_matrix_val(M, j, i));
		}
		err = printf("\n");
	}
	err = printf("\n");
	return err;

}

alignment_matrices* new_alignment_matrices(int len_x, int len_y)
{
	alignment_matrices* new_align_mats = malloc(sizeof(alignment_matrices));
	if (new_align_mats == NULL) {return(NULL);}

	// new_align_mats.H = malloc(sizeof(dbl_matrix));
	new_align_mats->H = new_dbl_matrix(len_x, len_y);
	new_align_mats->D = new_int_matrix(len_x, len_y);
	new_align_mats->SL = new_dbl_matrix(len_x, len_y);
	new_align_mats->SLP = new_dbl_matrix(len_x, len_y);
	if (new_align_mats->H   == NULL ||
		new_align_mats->D   == NULL ||
		new_align_mats->SL  == NULL ||
		new_align_mats->SLP == NULL){return(NULL);}

	// TODO [ ] fill in fn
	return new_align_mats;
}

int destroy_alignment_matrices(alignment_matrices* a)
{
	destroy_dbl_matrix(a->H);
	destroy_int_matrix(a->D);
	destroy_dbl_matrix(a->SL);
	destroy_dbl_matrix(a->SLP);
	free(a);
	return(0);
}

/**********************************************************
 alignment struct
 **********************************************************/
alignment *new_alignment(sb_seq* query, sb_seq* subj, sb_seq* quals)
{
	alignment* my_new_alignment = malloc(sizeof(alignment));
	my_new_alignment->matrices = new_alignment_matrices(query->len, subj->len);
	my_new_alignment->query = *query;
	my_new_alignment->subject = *subj;
	my_new_alignment -> quals = *quals;

	if (my_new_alignment == NULL ||
		my_new_alignment->matrices == NULL){return(NULL);}

	return(my_new_alignment);
}

int destroy_alignment(alignment* a)
{
	destroy_alignment_matrices(a->matrices);
	free(a);
	return(0);
}

int reload_alignment

// TODO(2019-04-23): make sure new matrix and alignment definitions carry through to the
//  rest of this file...
// then work on TESTS

int setup_alignment(char subj[], int len_subj, char query[], int len_query, char quals[], int len_quals, alignment* almnt)
{
	sb_seq *new_subj = new_sb_seq(subj, len_subj, 0);
	sb_seq *new_query = new_sb_seq(query, len_query, 0);
	sb_seq *new_quals = new_sb_seq(quals, len_quals, 0);

	almnt =

	almnt->subject = *new_subj;
	almnt->query = *new_query;
	almnt->quals = *new_quals;
	almnt->matrices = malloc(sizeof(alignment_matrices));
	if (almnt->matrices == NULL){return(1);}
	return(0);
}

/*
 * prints to stdout a legible representation of the alignment
 * example:
 *		-ATGGCAAAGACCTGGCTTCTGTGAACAACTTGCTGAAAAAGCATCAGCTGCTAGAGGCAGACGTGTCAGTCACT
 *		*                                                              ||| ||||||||
 *		---------------------------------------------------------------GTG-CAGTCACT
 */
int print_alignment(sb_seq s, sb_seq q, char* cigar)
{
	size_t align_len = strlen(cigar);
	char *q_buff = malloc((align_len+1)+sizeof(char));
		if (q_buff == NULL){printf("there was an error allocating memory\n"); return(1);}

	char *s_buff = malloc((align_len+1)+sizeof(char));
		if (s_buff == NULL){printf("there was an error allocating memory\n"); return(1);}

	char *align_buff = malloc((align_len+1)+sizeof(char));
		if (align_buff == NULL){printf("there was an error allocating memory\n"); return(1);}

	int pos_q = 0;
	int pos_s = 0;

	for (int i=0; i < align_len; i++){
		switch(cigar[i] - 65)
		{
			case DIAG_MATCH:
				q_buff[i] = q.data[pos_q];
				s_buff[i] = s.data[pos_s];
				align_buff[i] = '|';
				pos_q++;
				pos_s++;
				break;

			case DIAG_MISMATCH:
				q_buff[i] = q.data[pos_q];
				s_buff[i] = s.data[pos_s];
				align_buff[i] = 'X';
				pos_q++;
				pos_s++;
				break;

			case DIAG_N:
				q_buff[i] = q.data[pos_q];
				s_buff[i] = s.data[pos_s];
				align_buff[i] = ' ';
				pos_q++;
				pos_s++;
				break;

			case INS_I:
				q_buff[i] = '-';
				s_buff[i] = s.data[pos_s];
				align_buff[i] = ' ';

				pos_s++;
				break;

			case INS_J:
				q_buff[i] = q.data[pos_q];
				s_buff[i] = '-';
				align_buff[i] = ' ';
				pos_q++;
				break;

			case EDGE_I:
				q_buff[i] = '-';
				s_buff[i] = s.data[pos_s];
				align_buff[i] = '-';
				pos_s++;
				break;

			case EDGE_J:
				q_buff[i] = q.data[pos_q];
				s_buff[i] = '-';
				align_buff[i] = '-';
				pos_q++;
				break;

			case ORIGIN:
				q_buff[i] = '-';
				s_buff[i] = '-';
				align_buff[i] = '*';
				break;
		}
	}

	q_buff[align_len] = '\0';
	s_buff[align_len] = '\0';
	align_buff[align_len] = '\0';

	printf("%s\n%s\n%s\n", q_buff, align_buff, s_buff);
	printf("%s\n%s\n%s\n", s.data, q.data, cigar);

	free(q_buff);
	free(s_buff);
	free(align_buff);
	return(0);
}


/* RT enzyme error plus the DNA polyermase enzyme error (per base) times the number of cycles of PCR
TODO: insert references for these numbers */
/* note: while not every molecule is subjected to each round of amplification (most of the sequences in a
reaction mixture will have been generated in the last few cycles), any error introduced earlier
would likewise be probabgated forward, so for a given sequence there was an opportunity for error
at each cycle
*/
const double probPCRError = 0.00001490711984999862 + (0.00001038461538461538 * 30.0);




/*
 * 	takes a PHRED+33 encoded quality score from the sequencer and returns the probability of a
 * 	sequencer miscall, as a double floating point number
 */
double inline phredToProbIncorrect(char p)
{
	int phred = (int)p - 33;
	// printf("pred int for %c: %i\n", p, phred);
	double prob = pow(10, (-((double)phred) / 10.0));
	// printf("pred prob of miscall for %c: %f\n", p, prob);
	return prob;
}

/* takes an array of three doubles, and returns the index of the largest one
 */
int inline max_match(double values[3])
{
	int maxIndex = 0;

	for (int i = 1; i < 3; i++)
	{
		if (values[i] > values[maxIndex])
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

/*
 * takes two char values and compares them. The result of this comparison is translated into a
 * matrix_move and returned
 */
matrix_move inline match(char s, char q)
{
	matrix_move new_move;
	if (q =='N')
	{
		new_move = DIAG_N;
	}
	else if (q == s)
	{
	new_move = DIAG_MATCH;
	}
	else
	{
		new_move = DIAG_MISMATCH;
	}

	return(new_move);
}

// calculates the per base P(S|L,m), given the individual bases for the subject, the query, and
// the sequencer reported quality score for the query base.
double inline probSLMatch(char s, char q, char q_qual)
{
	double probMisscall = phredToProbIncorrect(q_qual);

	double probCorrcall = 1.0 - probMisscall;

	double value = (probPCRError * probMisscall) + (probCorrcall * (1.0 - probPCRError));

	return(value);
}

// calculates the per base P(S|L,x)
double inline probSLMismatch(char s, char q, char q_qual)
{
	double probMisscall = phredToProbIncorrect(q_qual);

	double probCorrcall = 1.0 - probMisscall;

	double value = (1.0 / 3.0 * probMisscall * (1.0 - probPCRError))
	             + (1.0 / 3.0 * probCorrcall * probPCRError)
	             + (2.0 / 9.0 * probMisscall * probPCRError);

	return value;
}




// TODO: refactor code a bit:
// make alignment matrices, traceback, test/trim, all seperate...testable things
// TODO: refactor to return a pointer to an alignment object containing all of the matrices
int fill_matrices(alignment *input, alignment_matrices align_mat)
{
	char* subj = input->subject.data;
	char* query = input->query.data;
	char* query_quals = input->quals.data;
    size_t max_i = input->subject.len + 1;
    size_t max_j = input->query.len + 1;

	// printf("max_i: %zu\n", max_i);
	// printf("max_j: %zu\n", max_j);
    double (*H)[max_j] = (double (*)[max_j]) align_mat.H;
	int (*D)[max_j] = (int (*)[max_j]) align_mat.D;

    double (*SL)[max_j] = (double (*)[max_j]) align_mat.SL;
    double (*SLP)[max_j] = (double (*)[max_j]) align_mat.SLP;

	for (int i = 0; i< max_i; i++)
	{
		for (int j = 0; j < max_j; j++)
		{
			if (i == 0 || j == 0)
			{
				H[i][j] = 0;
				SL[i][j] = 1;
				SLP[i][j] = 1;
				if (i == 0 && j == 0)
				{
					D[0][0] = ORIGIN;
				}
				else if (i == 0 && j > 0)
				{
					D[0][j] = INS_J;
				}
				else if (i > 0 && j == 0)
				{
					D[i][0] = INS_I;
				}
			}
			else
			{
				 matrix_move diag_move = match(subj[i-1], query[j-1]);

				double diag_value = 0;

				double diag_PSL = 0;

				double diag_PSLP = 0;
				switch (diag_move)
				{
					case DIAG_MATCH:
						diag_PSL = probSLMatch(subj[i-1], query[j-1], query_quals[j-1]);
						diag_PSLP = 0.25;
						diag_value = H[i-1][j-1] + log(diag_PSL / 0.25);
						break;

				 	 case DIAG_MISMATCH:
					 	diag_PSL = probSLMismatch(subj[i-1], query[j-1], query_quals[j-1]);
						diag_PSLP = 0.75;
						diag_value = H[i-1][j-1] + log(diag_PSL / 0.75);
						break;

					case DIAG_N:
						diag_PSL = 1;
						diag_PSLP = 1;
						diag_value = H[i-1][j-1];
						break;

					default:
						diag_PSL = 1;
						diag_PSLP = 1;
						diag_value = H[i-1][j-1];
						break;
				}

				// // printf("diag_value: %f\n", diag_value);

				// // printf("diag_PSL: %f\n", diag_PSL);

				// // printf("diag_PSLP: %f\n", diag_PSLP);

				double gap_i = H[i-1][j] + log(probPCRError);

				double gap_j = H[i][j-1] + log(probPCRError);

				int best_move = max_match( (double[3]){diag_value, gap_i, gap_j});
				switch (best_move)
				{
					case 0:
					// when the diagonal value is largest
						H[i][j] = diag_value;
						D[i][j] = diag_move;
						SL[i][j] = SL[i-1][j-1] * diag_PSL;
						SLP[i][j] = SLP[i-1][j-1] * diag_PSLP;

						break;

					case 1:
					// when the gap_i value is largest
						H[i][j] = gap_i;
						D[i][j] = INS_I;
						SL[i][j] = SL[i-1][j] * probPCRError;
						SLP[i][j] = SLP[i-1][j];

						break;

					case 2:
					// when the gap_j value is largest
						H[i][j] = gap_j;
						D[i][j] = INS_J;
						SL[i][j] = SL[i][j-1] * probPCRError;
						SLP[i][j] = SLP[i][j-1];
						break;
				}
			}
		}
	}
	//
	// print_dbl_matrix(max_i, max_j, H);
	//
	// print_dbl_matrix(max_i, max_j, SL);
	//
	// print_dbl_matrix(max_i, max_j, SLP);
	//
	// printf("%i\n", (int)max_j);
    // printf("dir matrix:\n");
	//
	//
	//
	// print_int_matrix(max_i, max_j, D);


	return(0);
}

char *traceback(alignment *input, int max_i, int max_j)
{
	// **** FIND HIGHEST VALUE ****
	// finds the highest value in the last column or last row of matrix H
	int highest_score_i = max_i-1;
	int highest_score_j = max_j-1;


	double (*H)[max_j] = (double (*)[max_j]) input->matrices->H;


	double (*D)[max_j] = (double (*)[max_j]) input->matrices->D;
	double (*SL)[max_j] = (double (*)[max_j]) input->matrices->SL;
	double (*SLP)[max_j] = (double (*)[max_j]) input->matrices->SLP;

	double highest_score = H[highest_score_i][highest_score_j];
	for (int i = 1; i < max_i; i++)
	{
		if (H[i][max_j-1] > highest_score)
		{
			highest_score = H[i][max_j-1];
			highest_score_i = i;
			highest_score_j = max_j-1;
		}
	}
	for (int j = 1; j < max_j-1; j++)
	{
		if (H[max_i-1][j] > highest_score)
		{
			highest_score = H[max_i-1][j];
			highest_score_i = max_i-1;
			highest_score_j = j;
		}
	}

	// printf("highest_i: %i\nhighest_j: %i\n", highest_score_i, highest_score_j);

	// ***** PROBABILITY TESTING ****

	// [x] TODO: bayesian prob test
	// calc P(L|S) and P(L'|S), for the alignment, print out true or false


	double psl_final = SL[highest_score_i][highest_score_j];
	double pslp_final = SLP[highest_score_i][highest_score_j];

	double apriori_pl = 0.5;

	double pls = (apriori_pl * psl_final) /
					(
						(psl_final * apriori_pl) +
						(pslp_final * (1 - apriori_pl))
					);

	double plps = ((1 - apriori_pl) * pslp_final) /
					(
						(pslp_final * apriori_pl) +
						(pslp_final * (1 - apriori_pl))
					);

	if (pls < plps)
	{
		// printf("%2e, %2e\n", pls, plps);
		// printf("hello: apparently the best alignmeent is not a linker\n");
	}
	// **** TRACEBACK ****
	// tracebacks and creates the reverse cigar and then cigar string representations of the
	// alignment

	int tback_pos_i = highest_score_i;
	int tback_pos_j = highest_score_j;
	matrix_move curr_dir = D[highest_score_i][highest_score_j];
	matrix_move rev_cigar[max_i + max_j];

	int rev_cigar_pos = 0;
	rev_cigar[rev_cigar_pos] = curr_dir;

	// the cigar string will represent thet alignment with respect to the query sequences
	// and any gaps will be filled in with enum matrix_move == GAP
	while (curr_dir != ORIGIN)
	{
		// // printf("tback_pos_i: %i \ntback_pos_j: %i\n\n", tback_pos_i, tback_pos_j);
		switch(curr_dir)
		{
			case DIAG_MATCH:
			// diagonal move because of a MATCH
				tback_pos_i = tback_pos_i - 1;
				tback_pos_j = tback_pos_j - 1;
				break;

			case DIAG_MISMATCH:
			// diagonal move because of a mismatch
				tback_pos_i = tback_pos_i - 1;
				tback_pos_j = tback_pos_j - 1;
				break;

			case DIAG_N:
			// diagonal move because of the query string has an "N"
				tback_pos_i = tback_pos_i - 1;
				tback_pos_j = tback_pos_j - 1;
				break;

			case INS_I:
			// insertion in the "i" direction
				tback_pos_i = tback_pos_i - 1;
				break;

			case INS_J:
			// insertion in the "j" direction
				tback_pos_j = tback_pos_j - 1;
				break;

			case EDGE_I:
			// reached an edge in the i direction
				tback_pos_i = tback_pos_i - 1;
				break;

			case EDGE_J:
			// reached an edge in the j direction
				tback_pos_j = tback_pos_j - 1;
				break;

			case  ORIGIN:
			// have reached the ORIGIN
			// this should never run
				break;
		}
		curr_dir = D[tback_pos_i][tback_pos_j];
		rev_cigar_pos ++;
		rev_cigar[rev_cigar_pos] = curr_dir;

	}

	matrix_move cigar[rev_cigar_pos+1];

	// printf("rev-cigar_pos: %i\n", rev_cigar_pos);

	char* cigar_str = malloc((rev_cigar_pos+1)*sizeof(char));
	// error check on the malloc call:
	if (cigar_str == NULL){printf("there was an error allocating memory\n"); return(NULL);}

	// printf("here\n");
	// invert the reverse cigar into a proper cigar string
	for (int i = 0; i < rev_cigar_pos+1; i++)
	{
		cigar[i] = rev_cigar[rev_cigar_pos - i];
		// printf("rev cigar val no: %i is %i\n", i, rev_cigar[rev_cigar_pos-1-i]);
		cigar_str[i] = (char) rev_cigar[rev_cigar_pos - i]+65;
	}
	cigar_str[rev_cigar_pos] = '\0';

	// printf("%s\n", cigar_str);

	// [x] TODO: alignment representation
	print_alignment(input->subject, input->query, cigar_str);


	// TODO: make more robust so that a read and linker can be inputted, they are processed, and
	// then the clean linker is returned...

	// TODO: make a verbose version that prints to stdout data re: cutting

	return cigar_str;
}




// TODO: deal with conflicts on matrix creation? two dirs with same value? (I feel like this is really unlikely)
