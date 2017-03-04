#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    size_t i;

    for (i = 1; ; i++)
    {
        if ((i % 100) == 0)
        {
            printf("i is: %zu", i);
        }
        char *p = (char *)malloc(i * 1024*1024);
        if (p == 0)
            break;
        *p = 13;
        free(p);
    }

    printf ("Allocated max %lu MB\n", (i - 1));

    return 0;
}
