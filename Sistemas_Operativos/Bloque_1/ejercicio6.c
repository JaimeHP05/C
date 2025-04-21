#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int count=0;
	
void controlador(int sig) {
	if (count == 0) {
		alarm(3);
		printf("RING\n");
	}
	if (count == 4) {
		kill(getpid(), SIGTERM);
	}
	if (count != 0) {
		alarm(1);
		printf("RING\n");
	}
	count++;
}

int main() {
	alarm(5); //Primera alarma en 5 segundos
	signal(SIGALRM, controlador);
	while (1) {
//Bucle infinito (aunque se detendrá con la señal SIGTERM)
	}
	return 0;
}
