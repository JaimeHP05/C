#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Uso: %s <número> <número>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		execlp("./factorial", "./factorial", argv[1], NULL);
		printf("execlp ha dado error.");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0) {
		execlp("./factorial", "./factorial", argv[2], NULL);
		printf("execlp ha dado error.");
		exit(EXIT_FAILURE);
	}
}
