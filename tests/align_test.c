#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <strings.h>
#include <stdlib.h>

#include "../align.h"


double get_time(void)
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec*1e-6;
}


char query[] = "GTGTCAGTCAC";
char subject[] = "GGTCTGTCC";

// should get
//
// GTGTCAGTCAC
// | |||x||| |
// G-GTCTGTC-C


// bool test_new_seq(void)
// {
//     seq *new_query = new_seq(query, sizeof(query) );
//     if (new_query == NULL){return(false);}
//
//     for (int i = 0; i< sizeof(query); i++)
//     {
//         if (new_query->data[i] != query[i])
//         {
//             return(false);
//         }
//         if (new_query->len != sizeof(query))
//         {
//             return(false);
//         }
//     }
//
//     return(true);
// }

// int setup_alignment(char subj[], int len_subj, char query[], int len_query, char quals[], int len_quals, alignment* loc){

bool test_setup_alignment(void)
{
    return(true);
}

int main(void)
{
	double start = get_time();

	// printf("start:\t%1.5f\n", start);
	alignment_matrices matrices;
	size_t max_i = 101;
	size_t max_j = 101;
	matrices.D   = (int*)    malloc(sizeof(int)    * max_i * max_j);
	matrices.H   = (double*) malloc(sizeof(double) * max_i * max_j);
	matrices.SL  = (double*) malloc(sizeof(double) * max_i * max_j);
	matrices.SLP = (double*) malloc(sizeof(double) * max_i * max_j);

	for (int i = 0; i < 1; i++)
	{
		char *subject = "GTGCAGTCACTT";

		char* query =
			"ATGGCAAAGACCTGGCTTCTGTGAACAACTTGCTGAAAAAGCATCAGCTGCTAGAGGCAGACGTGTCAGTCACTTC";
			                                                              // GTG-CAGTCACTT
		char* quals = "JIACCGGIBD?F??9BFFHI<GDGGIIGIDEECEHHCEEFC=CCCD:@A@A@>:>:??B@@B>?@C8@@>>>::>>";

		alignment *new_alignment = malloc(sizeof(alignment));
		if (new_alignment == NULL){return(1);}

		memcpy(new_alignment->subject.data, subject, 100);
		memcpy(new_alignment->query.data, query, 100);
		memcpy(new_alignment->quals.data, quals, 100);

		new_alignment->subject.len = strlen(subject);
		new_alignment->query.len = 76;
		new_alignment->quals.len = 76;

		// TODO: get the matrices in here
		int err;
		err  = fill_matrices(new_alignment, matrices);
		if (err != 0){return(1);}

		char* new_cigar;

		// TODO: fix traceback
		// new_cigar = traceback(new_alignment, 76, 76);
		new_cigar = "this is a test";
		char* test_cigar;
		test_cigar = "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEAAAEAAAAAAAA";

		if (strcmp(new_cigar, test_cigar) == 0 )
		{
			printf("test passes\n");
		}
		else
		{
			printf("tests did NOT pass\n");
		}
	}

	free(matrices.D);
	free(matrices.H);
	free(matrices.SL);
	free(matrices.SLP);
	double end = get_time();

	printf("end:\t%1.5f\n", end-start);

	return(0);
}
