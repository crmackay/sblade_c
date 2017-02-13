// #include <unity.h>
#include "align.c"

#include <stdbool.h>



char query[] = "GTGTCAGTCAC";
char subject[] = "GGTCTGTCC";

// should get
//
// GTGTCAGTCAC
// | |||x||| |
// G-GTCTGTC-C

// seq* new_seq(char input[], int len)


bool test_new_seq(void)
{
    seq *new_query = new_seq(query, sizeof(query) );
    if (new_query == NULL){return(false);}

    for (int i = 0; i< sizeof(query); i++)
    {
        if (new_query->data[i] != query[i])
        {
            return(false);
        }
        if (new_query->len != sizeof(query))
        {
            return(false);
        }
    }

    return(true);
}

// int setup_alignment(char subj[], int len_subj, char query[], int len_query, char quals[], int len_quals, alignment* loc){

bool test_setup_alignment(void)
{
    return(true);
}
