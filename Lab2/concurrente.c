// tiempo_concurrente.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    clock_t inicio, fin;
    double tiempo_usado;
    pid_t hijo1, hijo2, hijo3;
    volatile long long suma = 0;
    
    inicio = clock();
    
    hijo1 = fork();
    
    if(hijo1 == 0) {
        // Proceso hijo
        hijo2 = fork();
        
        if(hijo2 == 0) {
            // Proceso nieto
            hijo3 = fork();
            
            if(hijo3 == 0) {
                // Proceso bisnieto - ejecuta su ciclo
                int i;
                for(i = 0; i < 10000000; i++) {
                    suma += i;
                }
                return 0;
            } else {
                // Proceso nieto - ejecuta su ciclo
                int i;
                for(i = 0; i < 10000000; i++) {
                    suma += i;
                }
                wait(NULL); // Espera al bisnieto
                return 0;
            }
        } else {
            // Proceso hijo - ejecuta su ciclo
            int i;
            for(i = 0; i < 10000000; i++) {
                suma += i;
            }
            wait(NULL); // Espera al nieto
            return 0;
        }
    } else {
        // Proceso padre - NO ejecuta ciclo, solo espera
        wait(NULL); // Espera al hijo
        
        fin = clock();
        tiempo_usado = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo transcurrido (concurrente): %f segundos\n", tiempo_usado);
    }
    
    return 0;
}