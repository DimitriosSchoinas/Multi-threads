#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int num_target, num_threads;
int current_thread = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count_sequence(void *arg) {
    int thread_id = *((int *)arg);

    for (int i = 0; i <= num_target; i++) {
        pthread_mutex_lock(&mutex);
        while (current_thread != thread_id) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("hello from %c: %d\n", 'A' + thread_id, i);
        current_thread = (current_thread + 1) % num_threads;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    num_threads = atoi(argv[1]);
    num_target = atoi(argv[2]);

    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, count_sequence, &thread_ids[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

