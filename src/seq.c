#include <stdlib.h>
#include <strings.h>

#include "seq.h"

sb_seq* new_sb_seq(char input[], int len)
{
    sb_seq *next_sb_seq;
    next_sb_seq = (sb_seq*)malloc(sizeof(sb_seq));
    if (next_sb_seq == NULL){return(NULL);};

    next_sb_seq ->len = len;

    // void *memcpy(void *str1, const void *str2, size_t n)
    void* err = memcpy(next_sb_seq->data, input, len);
    if (err == NULL){return(NULL);}
    next_sb_seq->data[len+1]='\n';

    return(next_sb_seq);
}
