// Recuerda compilar usando -lpthread
// gcc ej3.c -o ej3 -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#define CHECK_ERROR(ret, msg) if (ret != 0) {errno = ret; printf("%s: %s\n", msg, errno); exit(EXIT_FAILURE);}

typedef struct {
    int *vector;
    int inicio;
    int final;
    int suma;
} DatosHebra;

void* funcion_hebra(void *arg) {
    DatosHebra *datos = (DatosHebra*) arg;
    int suma = 0;
    for (int i = datos->inicio; i < datos->final; i++) {
        suma += datos->vector[i];
    }
    datos->suma = suma;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número de hebras (2 o 5)>\n", argv[0]);
        return 1;
    }
    int num_hebras = atoi(argv[1]);
    if (num_hebras != 2 && num_hebras != 5) {
        printf("Número de hebras inválido. Debe ser 2 o 5.\n");
        return 1;
    }
    int vector[10];
    srand(time(NULL));
    printf("Vector completo: ");
    for (int i = 0; i < 10; i++) {
        vector[i] = rand() % 9 + 1;
        printf("%d ", vector[i]);
    }
    printf("\n\n");
    pthread_t hebras[num_hebras];
    DatosHebra datos[num_hebras];
    int nelem = 10 / num_hebras;
    int inicio = 0;
    for (int i = 0; i < num_hebras; i++) {
        datos[i].vector = vector;
        datos[i].inicio = inicio;
        datos[i].final = inicio + nelem;
        if (i == num_hebras - 1) {
            datos[i].final = 10; // Asegurar que la última hebra procese hasta el final del vector
        }
        int ret = pthread_create(&hebras[i], NULL, funcion_hebra, &datos[i]);
        CHECK_ERROR(ret, "Error creando hebra");
        inicio += nelem;
    }
    int total_suma = 0;
    for (int i = 0; i < num_hebras; i++) {
        int ret = pthread_join(hebras[i], NULL);
        CHECK_ERROR(ret, "Error esperando hebra");
        total_suma += datos[i].suma;
    }
    printf("La suma total del vector es: %d\n", total_suma);
    return 0;
}
