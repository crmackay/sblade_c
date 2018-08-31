#ifndef seq_H
#define seq_H

// defining a sequence as just an array of bytes
// TODO: create dynamic length via a pointer to an array of set length
typedef struct seq
{
    int len;        // length of the sequence
    char data[200]; // the actual data as an array of chars
    char *encoding;  // encoding information if appropriate
} seq;

// takes an array of chars and it length, and outputs a pointer to a seq struct
//      returns NULL if an allocation error occurs
seq* new_seq(char input[], int len);

#endif
