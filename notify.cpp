
//#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int buffer[100];

int duration = 20;
int length = 0;

void *producer(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;
    for(int i = 0; i < duration; i++) {

        // Request lock
        pthread_mutex_lock (&mutex);

        // Add an element to the buffer safely.
        buffer[length] = i;
        length++;
        printf("Producer %s length %d\n",str, length);

        // Signal the consumer thread a new element is available
        pthread_cond_signal(&cond);

        // Yield the lock.
        pthread_mutex_unlock (&mutex);

        // Simulate work.
        usleep(1);
    }

    return NULL;
}

void *consumer(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;
    for(int i = 0; i < duration; i++) {

        // Request lock
        pthread_mutex_lock (&mutex);

        // Check if there elements in the buffer.
        // Note this only works for 1-to-1 producer consumer
        if(length == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Decrease the count.
        length--;

        // Add an element to the buffer safely.
        int temp = buffer[length];
        printf("Consumer %s value %d\n",str, temp);

        // Yield the lock.
        pthread_mutex_unlock (&mutex);

        // Simulate work
        usleep(2);
    }

    return NULL;
}

/**
 * Example with two threads incrementing a shared variable
 * with a mutex.
 */
int main(int argc, char *argv[]) {

    pthread_t producer_thread;
    pthread_t consumer_thread;
    int i = 0;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads.
    pthread_create(&producer_thread, 0, producer, (void *) "1");
    pthread_create(&consumer_thread, 0, consumer, (void *) "1");

    //void ** retval;

    // wait for our thread to finish before continuing
    pthread_join(producer_thread, 0);
    pthread_join(consumer_thread, 0);

    // Clean up the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}