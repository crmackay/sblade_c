#ifndef fastq_H
#define fastq_H

#include "seq.h"
#include <stdio.h>


// defining a sequence as just an array of bytes
// TODO: create dynamic length via a pointer to an array of set length


typedef struct sb_fastq_read
{
    sb_seq  dna;
    sb_seq  qual;
    sb_seq  misc;
    sb_seq  id;
} sb_fastq_read;

typedef struct sb_fastq_file
{
    FILE* fp;
} sb_fastq_file;

int open_fastq(char* file_name);

int fastq_read_next(sb_fastq_read*);

#endif
