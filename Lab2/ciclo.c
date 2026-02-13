// fork_ciclo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Proceso inicial PID: %d\n", getpid());
    
    // Fork dentro de un ciclo for de 4 iteraciones
    for(int i = 0; i < 4; i++) {
        fork();
    }
    
    printf("Proceso PID: %d, Padre PID: %d\n", getpid(), getppid());
    
    return 0;
}