// Recuerda compilar usando -lpthread
// gcc ej2.c -o ej2 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define CHECK_ERROR(ret, msg) if (ret != 0) {errno = ret; printf("%s: %s\n", msg, errno); exit(EXIT_FAILURE);}

typedef struct {
    char *nombre;
    int nlineas;
} DatosHebra;

void* funcion_hebra(void* arg) {
    DatosHebra* datos = (DatosHebra*)arg;
    FILE *fichero = fopen(datos->nombre, "r");
    if (fichero == NULL) {
        printf("Error abriendo %s: %s\n", datos->nombre, strerror(errno));
        pthread_exit(NULL);
    }
    // Contar líneas
    	int c = 0;
	while ((c = fgetc(fichero)) != EOF) {
		if (c == '\n') {
			datos->nlineas++;
		}
	}
    printf("Archivo %s: %d líneas\n", datos->nombre, datos->nlineas);
    fclose(fichero);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <fichero1> [fichero2] ...\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int nficheros = argc - 1;
	pthread_t hebras[nficheros];
	DatosHebra datos[nficheros];

    // Crear hebras
    for (int i = 0; i < nficheros; i++) {
        datos[i].nombre = argv[i + 1];
        datos[i].nlineas = 0;
        int ret = pthread_create(&hebras[i], NULL, funcion_hebra, &datos[i]);
        CHECK_ERROR(ret, "Error creando hebra");
    }

    // Esperar hebras y sumar resultados
    int total = 0;
    for (int i = 0; i < nficheros; i++) {
        int ret = pthread_join(hebras[i], NULL);
        CHECK_ERROR(ret, "Error esperando hebra");
        total += datos[i].nlineas;
    }

    printf("\nTotal: %d líneas en %d archivos\n", total, nficheros);

    return EXIT_SUCCESS;
}
