#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int func(int id) {
    sleep(10);
    return 0;
}

int *thread_container_func(void *arg) {
    int *thread_id = (int*) arg;
    func(*thread_id);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {

    pthread_t threads[atoi(argv[1])];
    struct timespec inic, fim;
    double etime, total_time;
    int i;

    for (i=0; i<atoi(argv[1]); i++) {
        // Verifica o instante atual antes do bloco de código sendo medido
        if (clock_gettime(CLOCK_REALTIME, &inic) < 0)
            printf("Erro em clock_gettime");
        
        pthread_create(&(threads[i]), NULL, thread_container_func, &i);
        // Verifica o instante atual logo depois do bloco de código sendo medido
        if (clock_gettime(CLOCK_REALTIME, &fim) < 0)
            printf("Erro em clock_gettime");
            
        // tempo decorrido: elapsed time
        etime = (fim.tv_sec + fim.tv_nsec) - (inic.tv_sec + inic.tv_nsec);
        total_time += etime;
    }

    printf ("Mean thread creation time: %2f\n", total_time/10e9);
    pthread_exit(NULL);
}