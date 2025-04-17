#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <número_de_hijos>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int num_hijos = atoi(argv[1]);

	// Proceso padre
	pid_t pid;
	for (int i = 0; i < num_hijos; i++) {
		pid = fork();
		if (pid < 0) {
			printf("Error, el pid es menor o igual a 0.");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			// Proceso hijo
			printf("Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
		} else if (pid > 0) {
			int status;
			printf("Soy el padre %d\n", getpid());
			wait(&status);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
