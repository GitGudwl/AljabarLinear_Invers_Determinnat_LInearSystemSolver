#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
volatile long int g = 50;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// procedure to increaase the global variable g by 1
void *myThreadFun(void *vargp)
{
    pthread_mutex_lock(&mtx);
    // Store the value argument passed to this thread

    printf("(1)Increament Process Thread Address: %p, Global: %ld\n", (int *)vargp, g = g + 1);

    pthread_mutex_unlock(&mtx);
}

// procedure to decreaase the global variable g by 1
void *myThreadnotFun(void *vargp)
{
    pthread_mutex_lock(&mtx);
    // Store the value argument passed to this thread

    // Print the argument, static and global variables
    printf("(2)Decrement Process Thread Address: %p, Global: %ld\n", (int *)vargp, g = g - 1);

    pthread_mutex_unlock(&mtx);
}

int main()
{
    int i;
    pthread_t tid, tid2;

    // Let us create three threads
    for (i = 0; i < 50; i++)
    {
        pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
        pthread_create(&tid2, NULL, myThreadnotFun, (void *)&tid2);
    }

    pthread_exit(NULL);
    return 0;
}