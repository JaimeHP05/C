#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//./ej4 gnome-calculator gedit hola adios

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Uso: %s <calculadora> <editor> archivo1 archivo2 ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	// Crear el primer hijo para la calculadora
	pid = fork();
	if (pid == 0) {
		execlp(argv[1], argv[1], NULL); // Ejecutar la calculadora [execlp para pocos archivos]
		printf("execlp ha dado error.");
		exit(EXIT_FAILURE);
	}
	// Crear el segundo hijo para el editor de texto
	pid = fork();
	if (pid == 0) {
		execvp(argv[2], argv+2); // Ejecutar el editor con los archivos [execvp para muchos archivos] (Empieza a partir del tercer valor porque los dos primeros son la calculadora y el editor de texto)
		printf("execvp ha dado error.");
		exit(EXIT_FAILURE);
	}
	// Proceso padre espera a los hijos
	int status;
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}

