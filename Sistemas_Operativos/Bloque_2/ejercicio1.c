//Recuerda compilar usando -lpthread
//gcc ej1.c -o ej1 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define CHECK_ERROR(ret, msg) if (ret != 0) {errno = ret; printf("%s: %s\n", msg, errno); exit(EXIT_FAILURE);}

typedef struct{
	double suma;
}DatosHebra;

void* funcion_hebra(void* arg){
	DatosHebra* datos = (DatosHebra*) arg;
	double num1, num2;
	num1 = (double)rand() / RAND_MAX;
	num2 = (double)rand() / RAND_MAX;
	datos->suma=num1+num2;
	printf("Suma de %.2f + %.2f = %.2f\n", num1, num2, datos->suma);
	pthread_exit(NULL);
}

int main() {
	srand(time(NULL));
	double suma_total=0;
	pthread_t hebras[4];
	DatosHebra datos[4];
	for(int i=0; i<4; i++) {
		int ret = pthread_create(&hebras[i], NULL, funcion_hebra, &datos[i]);
		CHECK_ERROR(ret, "Error creando hebra");
	}
	for(int i=0; i<4; i++) {
		int ret = pthread_join(hebras[i], NULL);
		CHECK_ERROR(ret, "Error esperando hebra");
		suma_total=suma_total+datos[i].suma;
	}
	printf("Suma total = %.2f\n", suma_total);
	return 0;
}
