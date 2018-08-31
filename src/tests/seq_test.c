#include <stdio.h>

#include "./test_framework.h"

#include "../align.h"



char sample[] = "GTGTCAGTCAC";

int main(void) {

    seq* test_seq;

    test_seq = malloc(sizeof(seq));

    if (test_seq == NULL) {
        return(FALSE);
    }
    printf("from seq_test\n");
}
