// ipc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define SHM_NAME "/mi_memoria_compartida"
#define SHM_SIZE 1024
#define PIPE_NAME "/tmp/mi_pipe_nombrado"

int main(int argc, char **argv) {
    if(argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    char x = argv[2][0];
    
    printf("I am %c\n", x);
    
    // Intentar crear memoria compartida
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    int soy_creador = 0;
    
    if(shm_fd >= 0) {
        // Soy el creador
        soy_creador = 1;
        printf("%c: Created new shared mem obj %d\n", x, shm_fd);
        
        // Configurar tamaño
        ftruncate(shm_fd, SHM_SIZE);
        
        // Crear pipe nombrado para enviar el file descriptor
        mkfifo(PIPE_NAME, 0666);
        printf("%c: Ptr created with value 0x%x\n", x, shm_fd);
        
        // Enviar file descriptor por pipe nombrado
        int pipe_fd = open(PIPE_NAME, O_WRONLY);
        write(pipe_fd, &shm_fd, sizeof(int));
        close(pipe_fd);
        
    } else if(errno == EEXIST) {
        // Ya existe, soy el segundo
        printf("%c: Shared mem obj already created\n", x);
        shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        
        // Recibir file descriptor por pipe nombrado
        int pipe_fd = open(PIPE_NAME, O_RDONLY);
        int received_fd;
        read(pipe_fd, &received_fd, sizeof(int));
        close(pipe_fd);
        
        printf("%c: Received shm fd: %d\n", x, received_fd);
        printf("%c: Ptr created with value 0x%x\n", x, shm_fd);
    } else {
        perror("shm_open");
        return 1;
    }
    
    // Mapear memoria compartida
    char *ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    
    // Inicializar memoria si soy creador
    if(soy_creador) {
        printf("%c: Initialized shared mem obj\n", x);
        memset(ptr, 0, SHM_SIZE);
    }
    
    // Crear pipe ordinario para comunicación padre-hijo
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    
    // Fork
    pid_t hijo = fork();
    
    if(hijo == 0) {
        // Proceso hijo - lee del pipe y escribe en memoria compartida
        close(pipefd[1]); // Cerrar escritura
        
        char caracter;
        int pos = strlen(ptr); // Posición actual en memoria compartida
        
        while(read(pipefd[0], &caracter, 1) > 0) {
            ptr[pos] = caracter;
            pos++;
            ptr[pos] = '\0'; // Mantener como string
        }
        
        close(pipefd[0]);
        munmap(ptr, SHM_SIZE);
        return 0;
        
    } else {
        // Proceso padre - itera y envía x al hijo cuando i es divisible entre n
        close(pipefd[0]); // Cerrar lectura
        
        int i;
        for(i = 0; i < SHM_SIZE; i++) {
            if(i % n == 0 && i != 0) {
                write(pipefd[1], &x, 1);
            }
        }
        
        close(pipefd[1]); // Cerrar pipe para que hijo termine read()
        wait(NULL); // Esperar al hijo
        
        // Pequeña pausa para que la otra instancia termine de escribir
        sleep(1);
        
        // Mostrar contenido de memoria compartida
        printf("%c: Shared memory has: %s\n", x, ptr);
        
        // Cleanup
        munmap(ptr, SHM_SIZE);
        close(shm_fd);
        
        // Si soy el creador, limpiar recursos
        if(soy_creador) {
            sleep(2); // Esperar a que el otro proceso termine
            shm_unlink(SHM_NAME);
            unlink(PIPE_NAME);
        }
    }
    
    return 0;
}