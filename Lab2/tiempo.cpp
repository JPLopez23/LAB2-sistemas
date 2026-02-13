// tiempo_secuencial.c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio, fin;
    double tiempo_usado;
    
    // Inicio del cronómetro
    inicio = clock();
    
    // Primer ciclo de un millón de iteraciones
    for(int i = 0; i < 1000000; i++) {
    }
    
    // Segundo ciclo de un millón de iteraciones
    for(int i = 0; i < 1000000; i++) {
    }
    
    // Tercer ciclo de un millón de iteraciones
    for(int i = 0; i < 1000000; i++) {
    }
    
    // Fin del cronómetro
    fin = clock();
    
    // Calcular tiempo transcurrido
    tiempo_usado = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("Tiempo transcurrido: %f segundos\n", tiempo_usado);
    
    return 0;
}