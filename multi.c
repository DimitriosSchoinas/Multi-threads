#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>


int num_threads, number;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count_thread(void *arg){

 int thread_id = *((int *)arg);

    for (int i = 0; i <= number; i++) {
        pthread_mutex_lock(&mutex);
        printf("hello from %c: %d\n", 'A' + thread_id, i);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);



}

void count(int nthreads){
    
    pthread_t threads[nthreads];
    int thread_ids[nthreads];

    for (int i = 0; i < nthreads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, count_thread, &thread_ids[i]);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }


	

}
int main( int argc, char *argv[]){


if ( argc != 3 ) {
        printf("Usage: %s <num_threads> <num_to_count>\n", argv[0]);
        return 1;
    }

int num_threads = atoi(argv[1]);
int number = atoi(argv[2]);

count(num_threads);


return 0;
}
