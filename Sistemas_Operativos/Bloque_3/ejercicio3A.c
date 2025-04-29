// Recuerda compilar usando -lpthread
// gcc ej3.c -o ej3 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int bufin = 0;
int buffout = 0;

sem_t s;  // Semáforo para la sección crítica
sem_t cn; // Semáforo para contar los espacios ocupados
sem_t pr; // Semáforo para contar los espacios libres

void* productor(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100; // Generar un valor aleatorio

        sem_wait(&pr); // Esperar a que haya espacio libre
        sem_wait(&s);  // Entrar a la sección crítica

        buffer[bufin] = item;
        printf("Productor produjo: %d en posición %d\n", item, bufin);
        bufin = (bufin + 1) % BUFFER_SIZE;

        sem_post(&s);  // Salir de la sección crítica
        sem_post(&cn); // Incrementar el contador de espacios ocupados

        sleep(1); // Simular tiempo de producción
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&cn); // Esperar a que haya un espacio ocupado
        sem_wait(&s);  // Entrar a la sección crítica

        int item = buffer[buffout];
        printf("Consumidor consumió: %d de posición %d\n", item, buffout);
        buffout = (buffout + 1) % BUFFER_SIZE;

        sem_post(&s);  // Salir de la sección crítica
        sem_post(&pr); // Incrementar el contador de espacios libres

        sleep(1); // Simular tiempo de consumo
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    srand(time(NULL));

    sem_init(&s, 0, 1);          // Inicializar semáforo de sección crítica a 1
    sem_init(&cn, 0, 0);         // Inicializar semáforo de espacios ocupados a 0
    sem_init(&pr, 0, BUFFER_SIZE); // Inicializar semáforo de espacios libres a BUFFER_SIZE

    pthread_create(&prod, NULL, productor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&s);
    sem_destroy(&cn);
    sem_destroy(&pr);

    return EXIT_SUCCESS;
}
