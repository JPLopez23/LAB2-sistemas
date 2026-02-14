// zombie.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t hijo = fork();
    
    if(hijo == 0) {
        // Proceso hijo - termina inmediatamente
        printf("Hijo terminando PID: %d\n", getpid());
    } else {
        // Proceso padre - ciclo infinito sin wait()
        printf("Padre PID: %d, Hijo PID: %d\n", getpid(), hijo);
        while(1) {
            // Ciclo infinito - el padre nunca hace wait()
            sleep(1);
        }
    }
    
    return 0;
}