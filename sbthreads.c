#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

//  from http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

int  count = 0;

#define COUNT_DONE  10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

#define NUM_CORES   4

void makeWork(){}

void *getAndDoWork(void *arg)
{
    // work here

    long threadid = (long) pthread_self();
    printf("thredid is: %lu\n", threadid);
    int tcount = 0;

    while (tcount < 20)
    {
        //  pthread_mutex_lock( &count_mutex );
        tcount += 1;
        //  count += 1;
        printf("Counter value functionCount1: %d \n", tcount);

        //  pthread_mutex_unlock( &count_mutex );
    }
    pthread_exit(NULL);
}

int main(void)
{
    makeWork();

    pthread_t threads[NUM_CORES];

    printf("running on %i cores\n", NUM_CORES);

    for (int i = 0; i < NUM_CORES; i++)
    {
        pthread_create( &threads[i], NULL, &getAndDoWork, NULL);
    }
    for (int j = 0; j < NUM_CORES; j++)
    {
        pthread_join( threads[j], NULL);
    }

   printf("Final count: %d\n",count);

   exit(EXIT_SUCCESS);
}
