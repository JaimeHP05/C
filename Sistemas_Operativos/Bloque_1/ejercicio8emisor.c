#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = atoi(argv[1]);

    // Verificar si el proceso existe
    if (kill(pid, 0) == -1) {
        perror("Error: el proceso no existe");
        return EXIT_FAILURE;
    }

    printf("Enviando SIGUSR1 al proceso %d\n", pid);
    if (kill(pid, SIGUSR1) == -1) {
        perror("Error al enviar SIGUSR1");
        return EXIT_FAILURE;
    }

    sleep(1);  // Espera demostrativa

    printf("Enviando SIGKILL al proceso %d\n", pid);
    if (kill(pid, SIGKILL) == -1) {
        perror("Error al enviar SIGKILL");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
