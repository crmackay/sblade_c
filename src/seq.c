#include <stdlib.h>
#include <strings.h>

#include "seq.h"

seq* new_seq(char input[], int len)
{
    seq *next_seq;
    next_seq = (seq*)malloc(sizeof(seq));
    if (next_seq == NULL){return(NULL);};

    next_seq ->len = len;

    // void *memcpy(void *str1, const void *str2, size_t n)
    void* err = memcpy(next_seq->data, input, len);
    if (err == NULL){return(NULL);}

    return(next_seq);
}
