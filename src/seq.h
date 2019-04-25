#ifndef seq_H
#define seq_H

#include <stddef.h>
// defining a sequence as just an array of bytes
// TODO: create dynamic length via a pointer to an array of set length
typedef struct sb_seq
{
    size_t len;        // length of the sequence
    char data[200]; // the actual data as an array of chars
    int encoding;  // encoding information if appropriate
} sb_seq;

// takes an array of chars and it length, and outputs a pointer to a seq struct
//      returns NULL if an allocation error occurs
sb_seq* new_sb_seq(char input[], size_t len, int enc);

int destroy_sb_seq(sb_seq* seq);

#endif
