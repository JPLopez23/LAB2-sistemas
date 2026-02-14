// zombie_largo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t hijo = fork();
    
    if(hijo == 0) {
        // Proceso hijo - conteo largo
        int i;
        for(i = 1; i <= 8000000; i++) {
            if(i % 500000 == 0) {
                printf("Hijo contando: %d\n", i);
            }
        }
        printf("Hijo terminado\n");
    } else {
        // Proceso padre - ciclo infinito
        printf("Padre PID: %d, Hijo PID: %d\n", getpid(), hijo);
        while(1) {
            sleep(1);
        }
    }
    
    return 0;
}