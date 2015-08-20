
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

void *threadFunc(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;

    while(i < 10)
    {
        usleep(1);
        // Show the thread is running
        printf("threadFunc says: %s\n",str);
        ++i;
    }

    return NULL;
}

/**
 * Basic example that showing threading interleaving.
 */
int main(int argc, char *argv[]) {

    // Thread object
    pthread_t pth;  
    int i = 0;

    // Create the thread.
    pthread_create(&pth, 0, threadFunc, (void *) "processing...");

    // Create worker thread
    void ** retval;

    // wait for our thread to finish before continuing
    //pthread_join(pth, retval);

    while(i < 10 )
    {
        usleep(1);
        printf("main() is running...\n");
        ++i;
    }

    // wait for our thread to finish before continuing
    pthread_join(pth, retval);

    return 0;
}