// fork_consecutivo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Proceso inicial PID: %d\n", getpid());
    
    fork();  // Primera llamada: 2 procesos
    fork();  // Segunda llamada: 4 procesos
    fork();  // Tercera llamada: 8 procesos
    fork();  // Cuarta llamada: 16 procesos
    
    printf("Proceso PID: %d, Padre PID: %d\n", getpid(), getppid());
    
    return 0;
}