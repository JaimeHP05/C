#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler_sigusr1(int signo) {
    printf("Proceso %d: Señal SIGUSR1 recibida\n", getpid());
}

int main() {
    // Configurar manejador de señal
    if (signal(SIGUSR1, handler_sigusr1) == SIG_ERR) {
        perror("Error al configurar signal");
        return EXIT_FAILURE;
    }

    printf("Proceso receptor iniciado. PID = %d\n", getpid());
    printf("Esperando señales...\n");

    // Bucle infinito esperando señales
    while(1) {
        pause();  // Espera más eficiente que while(1)
    }

    return EXIT_SUCCESS;
}
