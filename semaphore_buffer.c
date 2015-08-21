
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <pthread.h>
#include <semaphore.h>

sem_t producer_sem;
sem_t consumer_sem;

pthread_mutex_t mutex;
//pthread_cond_t cond;

#define MAX_LENGTH 10
#define MAX_THREAD_PROC 2
#define MAX_THREAD_CONS 2

int buffer[MAX_LENGTH];

int duration = 20;
int length = 0;

void *producer(void *arg)
{
    int str;

    str=(int)arg;
    for(int i = 0; i < duration; i++) {

        // Request lock
        sem_wait(&producer_sem);

        // Request lock
        pthread_mutex_lock(&mutex);

        // Add an element to the buffer safely.
        buffer[length] = i;
        length++;
        printf("Producer %d length %d\n",str, length);

        // Yield the lock.
        pthread_mutex_unlock(&mutex);

        // Signal the consumer thread a new element is available
        sem_post(&consumer_sem);

    }

    return NULL;
}

void *consumer(void *arg)
{
    int str;

    str=(int)arg;
    for(int i = 0; i < duration; i++) {

        // Check if the buffer contains values
        sem_wait(&consumer_sem);

        // Request lock
        pthread_mutex_lock(&mutex);

        // Decrease the count.
        length--;

        // Add an element to the buffer safely.
        int temp = buffer[length];
        printf("Consumer %d at %d, value %d\n",str, length, temp);

        // Yield the lock.
        pthread_mutex_unlock(&mutex);

        // Signal the producer thread an element slot is free
        sem_post(&producer_sem);
    }

    return NULL;
}

/**
 * Example with two threads incrementing a shared variable
 * with a mutex.
 */
int main(int argc, char *argv[]) {

    pthread_t producer_thread[MAX_THREAD_PROC];
    pthread_t consumer_thread[MAX_THREAD_CONS];

    // Initialize the semaphore.
    sem_init(&producer_sem, 0, MAX_LENGTH);
    sem_init(&consumer_sem, 0, 0);

    // Create two threads.
    for(int i = 0; i < MAX_THREAD_PROC; i++) {
        //int temp = 0;
        //memcpy(&temp, &i, sizeof(i));
        pthread_create(&producer_thread[i], 0, producer, (void *)(uintptr_t) i);
        pthread_create(&consumer_thread[i], 0, consumer, (void *)(uintptr_t) i);
    }

    // wait for our thread to finish before continuing
    for(int i = 0; i < MAX_THREAD_CONS; i++) {
        pthread_join(producer_thread[i], 0);
        pthread_join(consumer_thread[i], 0);
    }

    // Clean up
    sem_destroy(&producer_sem);
    sem_destroy(&consumer_sem);

    return 0;
}