// ipcRunner.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("os@debian:~$ ./ipcRunner.o\n");
    
    pid_t hijo1 = fork();
    
    if(hijo1 == 0) {
        // Primera instancia de ipc
        execl("./ipc", "ipc", "3", "a", NULL);
        perror("execl");
        return 1;
    }
    
    // Pequeña pausa para asegurar que la primera instancia cree la memoria primero
    usleep(200000); // 200ms
    
    pid_t hijo2 = fork();
    
    if(hijo2 == 0) {
        // Segunda instancia de ipc
        execl("./ipc", "ipc", "5", "b", NULL);
        perror("execl");
        return 1;
    }
    
    // Esperar a ambos hijos
    wait(NULL);
    wait(NULL);
    
    return 0;
}