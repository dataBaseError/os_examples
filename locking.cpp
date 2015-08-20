
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;

int count = 0;

void *runner(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;

    while(i < 10 )
    {
        pthread_mutex_lock (&mutex);
        count++;
        printf("%s says %i\n",str, count);
        pthread_mutex_unlock (&mutex);
        usleep(1);        
        ++i;
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t pth;
    pthread_t pth2;
    int i = 0;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pth, 0, runner, (void *) "Thread 1");
    pthread_create(&pth2, 0, runner, (void *) "Thread 2");

    /* Create worker thread */
    void ** retval;

    /* wait for our thread to finish before continuing */
    pthread_join(pth, retval);

    pthread_mutex_destroy(&mutex);

    return 0;
}