#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fastqio.h"


// TODO: add a check to make sure the fastq conforms to spec/standard/expectation?

// TODO: add support for stdin and stdout

typedef struct sb_seq
{
    char    seq[400];
    size_t  len;
} sb_seq;

// typedef struct sb_

typedef struct sb_fastq_read
{
    sb_seq  dna;
    sb_seq  qual;
    sb_seq  misc;
    sb_seq  id;
} sb_fastq_read;

sb_fastq_read new_sb_fastq_read(char *lines[4])
{
    sb_fastq_read new_read;

    // subtracting 1 to remove the new line from the length
    new_read.id.len = strlen(lines[0])-1;
    memcpy(new_read.id.seq , lines[0], new_read.id.len);

    new_read.dna.len = strlen(lines[1])-1;
    memcpy(new_read.dna.seq , lines[1], new_read.dna.len);

    new_read.misc.len = strlen(lines[2])-1;
    memcpy(new_read.misc.seq , lines[2], new_read.misc.len);

    new_read.qual.len = strlen(lines[3])-1;
    memcpy(new_read.qual.seq , lines[3], new_read.qual.len);

    return(new_read);
}


// next read returns error if there's an error
int next_read_from_file(FILE *fp, sb_fastq_read *next_read)
{
    int err = ferror(fp);
    if (err != 0) {return(1);}
    // int eof = feof(fp);
    char myChar = fgetc(fp);
    printf("3: %c\n", myChar);
    return(0);
}

// close file
int close (FILE *fp)
{
    fclose(fp);
    return(0);
}


int new_fastq_reader(){
    return(0);
}

int write_fastq(){
    return(0);
}

int main(void)
{

    FILE *my_fp;

    my_fp = fopen("sample.fastq", "r");

    char *line0 = (char*)malloc(sizeof(char)*500);
    char *line1 = (char*)malloc(sizeof(char)*500);
    char *line2 = (char*)malloc(sizeof(char)*500);
    char *line3 = (char*)malloc(sizeof(char)*500);

    char *lines[4] = {line0, line1, line2, line3};

    for (int j = 0; j<100; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            // TODO: add a check for longer lines
            // if a line longer than 500 chars is encounters, fgets will just fill fill the lines
            // buffer with 499 chars and a \0, and then process the rest of the line as another string
            char *read_err = fgets(lines[i], 500, my_fp);
            // but this also happens at EOF, so not necessariliy an error
            if (read_err == NULL)
            {
                fprintf(stderr, "meaningful message here\n");
                return(1);
            }
        }

        sb_fastq_read my_read = new_sb_fastq_read(lines);

        printf("read sequence: %c \n", my_read.dna.seq[0]);
    }

    int err = fclose(my_fp);
    if (err != 0)
    {
        return(2);
    }

    free(line0);
    free(line1);
    free(line2);
    free(line3);

    return(0);
    // printf("%s", my_read->seq);
    //
    // err = close(my_fp);
}
