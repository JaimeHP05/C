// Recuerda compilar usando -lpthread
// gcc ej1.c -o ej1 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *camisetas;
int num_modelos;
pthread_mutex_t *mutexes;

void* cliente(void* arg) {
    int id = *((int*)arg);
    int modelo = rand() % num_modelos;
    int cantidad = rand() % 10 + 1;

    pthread_mutex_lock(&mutexes[modelo]);
    if (camisetas[modelo] >= cantidad) {
        camisetas[modelo] -= cantidad;
        printf("Cliente %d compró %d camisetas del modelo %d\n", id + 1, cantidad, modelo + 1);
    } else {
        printf("Cliente %d compró %d camisetas del modelo %d (stock insuficiente)\n", id + 1, camisetas[modelo], modelo + 1);
        camisetas[modelo] = 0;
    }
    pthread_mutex_unlock(&mutexes[modelo]);

    return NULL;
}

void* proveedor(void* arg) {
    int id = *((int*)arg);
    int modelo = rand() % num_modelos;
    int cantidad = rand() % 10 + 1;

    pthread_mutex_lock(&mutexes[modelo]);
    camisetas[modelo] += cantidad;
    printf("Proveedor %d suministró %d camisetas del modelo %d\n", id + 1, cantidad, modelo + 1);
    pthread_mutex_unlock(&mutexes[modelo]);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <num_clientes> <num_modelos>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num_clientes = atoi(argv[1]);
    num_modelos = atoi(argv[2]);
    if (num_clientes <= 0 || num_modelos <= 0) {
        printf("El número de clientes y modelos debe ser mayor que 0.\n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    // Inicializar el buffer de camisetas y los mutexes
    camisetas = malloc(num_modelos * sizeof(int));
    mutexes = malloc(num_modelos * sizeof(pthread_mutex_t));
    if (camisetas == NULL || mutexes == NULL) {
        perror("Error al asignar memoria");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_modelos; i++) {
        camisetas[i] = rand() % 100 + 1;
        pthread_mutex_init(&mutexes[i], NULL);
    }

    // Imprimir el stock inicial
    printf("Stock inicial de camisetas:\n");
    for (int i = 0; i < num_modelos; i++) {
        printf("Modelo %d: %d\n", i + 1, camisetas[i]);
    }

    pthread_t *clientes = malloc(num_clientes * sizeof(pthread_t));
    pthread_t *proveedores = malloc(num_modelos * sizeof(pthread_t));
    int *ids = malloc((num_clientes + num_modelos) * sizeof(int));
    if (clientes == NULL || proveedores == NULL || ids == NULL) {
        perror("Error al asignar memoria");
        free(camisetas);
        free(mutexes);
        return EXIT_FAILURE;
    }

    // Crear hebras de clientes
    for (int i = 0; i < num_clientes; i++) {
        ids[i] = i;
        if (pthread_create(&clientes[i], NULL, cliente, &ids[i]) != 0) {
            perror("Error creando hebra cliente");
            free(camisetas);
            free(mutexes);
            free(clientes);
            free(proveedores);
            free(ids);
            return EXIT_FAILURE;
        }
    }

    // Crear hebras de proveedores
    for (int i = 0; i < num_modelos; i++) {
        ids[num_clientes + i] = i;
        if (pthread_create(&proveedores[i], NULL, proveedor, &ids[num_clientes + i]) != 0) {
            perror("Error creando hebra proveedor");
            free(camisetas);
            free(mutexes);
            free(clientes);
            free(proveedores);
            free(ids);
            return EXIT_FAILURE;
        }
    }
    // Esperar a que terminen las hebras de clientes
    for (int i = 0; i < num_clientes; i++) {
        pthread_join(clientes[i], NULL);
    }
    // Esperar a que terminen las hebras de proveedores
    for (int i = 0; i < num_modelos; i++) {
        pthread_join(proveedores[i], NULL);
    }
    // Imprimir el stock final
    printf("Stock final de camisetas:\n");
    for (int i = 0; i < num_modelos; i++) {
        printf("Modelo %d: %d\n", i + 1, camisetas[i]);
    }
    // Liberar recursos
    for (int i = 0; i < num_modelos; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }
    free(camisetas);
    free(mutexes);
    free(clientes);
    free(proveedores);
    free(ids);
    return EXIT_SUCCESS;
}
