// Recuerda compilar usando -lpthread
// gcc ej4.c -o ej4 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
sem_t semA;
sem_t semB;

void* escribirA(void* p) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&semA); // Esperar a que sea el turno de escribir "A"
        printf("A");
        fflush(NULL);
        sem_post(&semB); // Permitir que se escriba "B"
    }
    return NULL;
}

void* escribirB(void* p) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&semB); // Esperar a que sea el turno de escribir "B"
        printf("B");
        fflush(NULL);
        sem_post(&semA); // Permitir que se escriba "A"
    }
    return NULL;
}

int main() {
    pthread_t hiloA, hiloB;
    // Inicializar los semáforos
    sem_init(&semA, 0, 0); // Inicialmente no se puede escribir "A"
    sem_init(&semB, 0, 1); // Inicialmente se puede escribir "B"
    // Crear los hilos
    pthread_create(&hiloA, NULL, escribirA, NULL);
    pthread_create(&hiloB, NULL, escribirB, NULL);
    // Esperar a que terminen los hilos
    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);
    // Destruir los semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);
    return EXIT_SUCCESS;
}
