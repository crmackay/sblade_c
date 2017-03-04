#include "stdio.h"
#include <stdlib.h>
int main(void) {
    // Disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Hello World\n");
    int test[2][2][3];

    int* space = malloc(sizeof(int)*2*2*3*7);

    if (space == NULL){
    	printf("error allocating\n");
    	return(1);
    }

    int (*array)[2][3][7] = (int (*)[2][3][7]) space;

    array[1][1][2][6] = 54;
    test[1][1][2] = 2;

    printf("%i\n", array[1][1][2][6]);

    printf("%p\n", &array);


    printf("%i\n", test[1][1][2]);

    // printf("%i\n", array[1][1][3]);
    return 0;
}
