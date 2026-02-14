// tiempo_secuencial.c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio, fin;
    double tiempo_usado;
    
    inicio = clock();
    
    for(int i = 0; i < 1000000; i++) {
    }
    
    for(int i = 0; i < 1000000; i++) {
    }
    
    for(int i = 0; i < 1000000; i++) {
    }
    
    fin = clock();
    
    tiempo_usado = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("Tiempo transcurrido: %f segundos\n", tiempo_usado);
    
    return 0;
}
