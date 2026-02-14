	#include <stdio.h>
#include <time.h>

int main() {
    clock_t inicio, fin;
    double tiempo_usado;
    volatile long long suma = 0;
    
    inicio = clock();
    
    int i;
    for(i = 0; i < 10000000; i++) {
        suma += i;
        if(i % 1000 == 0) {
            printf("Ciclo 1 - i: %d\n", i);
        }
    }
    
    for(i = 0; i < 10000000; i++) {
        suma += i;
        if(i % 1000 == 0) {
            printf("Ciclo 2 - i: %d\n", i);
        }
    }
    
    for(i = 0; i < 10000000; i++) {
        suma += i;
        if(i % 1000 == 0) {
            printf("Ciclo 3 - i: %d\n", i);
        }
    }
    
    fin = clock();
    tiempo_usado = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo: %f segundos\n", tiempo_usado);
    
    return 0;
}
