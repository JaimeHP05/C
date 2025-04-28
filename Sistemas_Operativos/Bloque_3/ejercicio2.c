// Recuerda compilar usando -lpthread
// gcc ej2.c -o ej2 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int par = 0;
int impar = 0;
pthread_mutex_t mutex_par;
pthread_mutex_t mutex_impar;

typedef struct {
    int id;
    int suma;
} DatosHebra;

void* funcion_hebra(void* arg) {
    DatosHebra* datos = (DatosHebra*)arg;
    datos->suma = 0;

    for (int i = 0; i < 5; i++) {
        int num = rand() % 11; // Genera un número aleatorio entre 0 y 10
        datos->suma += num;

        if (datos->id % 2 == 0) {
            pthread_mutex_lock(&mutex_par);
            par += num;
            pthread_mutex_unlock(&mutex_par);
        } else {
            pthread_mutex_lock(&mutex_impar);
            impar += num;
            pthread_mutex_unlock(&mutex_impar);
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <num_hebras>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num_hebras = atoi(argv[1]);
    if (num_hebras <= 0) {
        printf("El número de hebras debe ser mayor que 0.\n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    pthread_t hebras[num_hebras];
    DatosHebra datos[num_hebras];
    pthread_mutex_init(&mutex_par, NULL);
    pthread_mutex_init(&mutex_impar, NULL);

    // Crear hebras
    for (int i = 0; i < num_hebras; i++) {
        datos[i].id = i + 1;
        if (pthread_create(&hebras[i], NULL, funcion_hebra, &datos[i]) != 0) {
            perror("Error creando hebra");
            return EXIT_FAILURE;
        }
    }
    // Esperar a que terminen las hebras
    for (int i = 0; i < num_hebras; i++) {
        pthread_join(hebras[i], NULL);
        printf("Hebra %d generó una suma total de: %d\n", datos[i].id, datos[i].suma);
    }

    // Imprimir los valores finales de las variables par e impar
    printf("Valor final de la variable 'par': %d\n", par);
    printf("Valor final de la variable 'impar': %d\n", impar);

    // Liberar recursos
    pthread_mutex_destroy(&mutex_par);
    pthread_mutex_destroy(&mutex_impar);

    return EXIT_SUCCESS;
}
