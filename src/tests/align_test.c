#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <strings.h>
#include <stdlib.h>

#include "../align.h"
#include "test_framework.h"


double get_time(void)
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec*1e-6;
}

//  TODO: add table driven testfile

char query[] = "GTGTCAGTCAC";
char subject[] = "GGTCTGTCC";
char answer[] = "AEAAABAAAEA";
// should get
//
// GTGTCAGTCAC
// | |||x||| |
// G-GTCTGTC-C


int test_new_int_matrix(void){
	int_matrix m = new_int_matrix(10, 20);
	if (m.loc != NULL){
		return(FAIL);
	}
	return(PASS);
}

int test_destroy_int_matrix(void){
		int_matrix m = new_int_matrix(10, 20);

		destroy_int_matrix(m);

		return(PASS);
}

int test_set_int_matrix_val(){
	int x = 11;
	int y = 9;
	int_matrix m = new_int_matrix(x,y);

	int pos_x = 0;
	int pos_y = 0;
	set_int_matrix_val(m, 0, 0, 0);
	if (m.loc[(m.num_cols * pos_y) + pos_x] == 0){
		return(PASS);
	}
	return (FAIL);
}

int test_get_int_matrix_val(){
	int x = 11;
	int y = 9;
	int_matrix m = new_int_matrix(x,y);

	int pos_x = 0;
	int pos_y = 0;
	int val = 10;
	m.loc[(m.num_cols * pos_y) + pos_x] = val;

	int t = get_int_matrix_val(m, 0, 0);
	if (t == val){
		return(PASS);
	}
	return (FAIL);
}

// void print_int_matrix(int rows, int cols, int m[rows][cols])
int test_print_int_matrix(){
	int x = 11;
	int y = 9;
	int_matrix m = new_int_matrix(x,y);

	int err = 0;
	err = print_int_matrix(m);
	if (err == -1){
		return(PASS);
	}
	return(FAIL);

}

// int main(void)
// {
// 	double start = get_time();
//
// 	// printf("start:\t%1.5f\n", start);
// 	alignment_matrices matrices;
// 	size_t max_i = 101;
// 	size_t max_j = 101;
// 	matrices.D   = (int*)    malloc(sizeof(int)    * max_i * max_j);
// 	matrices.H   = (double*) malloc(sizeof(double) * max_i * max_j);
// 	matrices.SL  = (double*) malloc(sizeof(double) * max_i * max_j);
// 	matrices.SLP = (double*) malloc(sizeof(double) * max_i * max_j);
//
// 	for (int i = 0; i < 1; i++)
// 	{
// 		char *subject = "GTGCAGTCACTT";
//
// 		char* query =
// 			"ATGGCAAAGACCTGGCTTCTGTGAACAACTTGCTGAAAAAGCATCAGCTGCTAGAGGCAGACGTGTCAGTCACTTC";
// 			                                                              // GTG-CAGTCACTT
// 		char* quals = "JIACCGGIBD?F??9BFFHI<GDGGIIGIDEECEHHCEEFC=CCCD:@A@A@>:>:??B@@B>?@C8@@>>>::>>";
//
// 		alignment *new_alignment = malloc(sizeof(alignment));
// 		if (new_alignment == NULL){return(1);}
//
// 		memcpy(new_alignment->subject.data, subject, 100);
// 		memcpy(new_alignment->query.data, query, 100);
// 		memcpy(new_alignment->quals.data, quals, 100);
//
// 		new_alignment->subject.len = strlen(subject);
// 		new_alignment->query.len = 76;
// 		new_alignment->quals.len = 76;
//
// 		// TODO: get the matrices in here
// 		int err;
// 		err  = fill_matrices(new_alignment, matrices);
// 		if (err != 0){return(1);}
//
// 		char* new_cigar;
//
// 		// TODO: fix traceback
// 		// new_cigar = traceback(new_alignment, 76, 76);
// 		new_cigar = "this is a test";
// 		char* test_cigar;
// 		test_cigar = "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEAAAEAAAAAAAA";
//
// 		if (strcmp(new_cigar, test_cigar) == 0 )
// 		{
// 			printf("test passes\n");
//
// 		}
// 		else
// 		{
// 			printf("tests did NOT pass\n");
// 			printf("%c - %c\n",new_cigar[0], test_cigar[0]);
// 		}
// 	}
//
// 	free(matrices.D);
// 	free(matrices.H);
// 	free(matrices.SL);
// 	free(matrices.SLP);
// 	double end = get_time();
//
// 	printf("end:\t%1.5f\n", end-start);
//
// 	return(0);
// }

int main(void){
	// TODO: add run_test(fn);
	test_new_int_matrix();
	test_destroy_int_matrix();
	test_set_int_matrix_val();
	test_get_int_matrix_val();
	test_print_int_matrix();

}
