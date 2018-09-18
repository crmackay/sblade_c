#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../seq.h"

#include "./test_framework.h"

// #include "../align.h"




int test(void){

    sb_seq* test_seq;
    char sample[] = "GTGTCAGTCAC";
    test_seq = malloc(sizeof(sb_seq));

    test_seq = new_sb_seq(sample,11);
    if (test_seq == NULL) {
        return(FAIL);
    }
    printf("from seq_test\n");
    printf("%s\n",test_seq->data);
    printf("%i\n",test_seq->len);
    return(PASS);
}


int main(void) {
    run_test(test, "test fn");

}
