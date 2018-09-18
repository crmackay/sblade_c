#ifndef TRUE
#define TRUE 1
#endif /* end of include guard:  */

#ifndef FALSE
#define FALSE 0
#endif /* end of include guard:  */

#ifndef PASS
#define PASS 2
#endif /* end of include guard:  */

#ifndef FAIL
#define FAIL 3
#endif /* end of include guard:  */

#include <stdio.h>

int run_test( int (*test_fn)(), char* name){
    int result = test_fn();
    if (result == PASS){
        printf("%s PASSED\n", name);
    } else if (result == FAIL) {
        printf("%s FAILED\n", name);
    }
    return(0);
}
