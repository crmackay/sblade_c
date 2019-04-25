#include <stdlib.h>
#include <strings.h>

#include "seq.h"

sb_seq* new_sb_seq(char input[], size_t len, int enc)
{
    sb_seq *next_sb_seq = malloc(sizeof(sb_seq));
    if (next_sb_seq == NULL){return(NULL);};

    next_sb_seq->len = len;
    next_sb_seq->encoding = enc;
    memcpy(next_sb_seq->data, input, len);

    return(next_sb_seq);
}

int destroy_sb_seq(sb_seq* seq)
{
    free(seq);
    return(0);
}
