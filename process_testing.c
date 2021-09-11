#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int func() {
    sleep(60);
    return 0;
}

int main (int argc, char **argv) {
    
    pid_t process[atoi(argv[1])];
    struct timespec inic, fim;
    double etime, total_time;
    int i;

    for (i=0; i<atoi(argv[1]); i++) {
        // Verifica o instante atual antes do bloco de código sendo medido
        if (clock_gettime(CLOCK_REALTIME, &inic) < 0)
            printf("Erro em clock_gettime");
        
        process[i] = fork();
        // Verifica o instante atual logo depois do bloco de código sendo medido
        if (clock_gettime(CLOCK_REALTIME, &fim) < 0)
            printf("Erro em clock_gettime");
        // tempo decorrido: elapsed time
        etime = (fim.tv_sec + fim.tv_nsec) - (inic.tv_sec + inic.tv_nsec);
        
        if (process[i] == -1) {
            exit(0);
        }
        
        if (process[i] == 0) {
            func();
            exit(0);
        }

        total_time += etime;
    }

    printf ("Mean process creation time: %2f\n", total_time/10e9);    
}