#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global counter for signals received
int contador = 0;

// Signal handler function
void tratarSennal(int sig) {
    contador++;
    printf("Hijo: Señal SIGUSR1 recibida (#%d)\n", contador);
    
    if (contador >= 5) {
        printf("Hijo: 5 señales recibidas. Terminando...\n");
        exit(0);
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Hijo: PID = %d iniciado\n", getpid());
        
        // Set up signal handler
        if (signal(SIGUSR1, tratarSennal) == SIG_ERR) {
            perror("Error en signal");
            exit(EXIT_FAILURE);
        }

        // Wait for signals
        while(1) {
            pause();
        }

    } else {
        // Parent process
        printf("Padre: Enviando señales a hijo (PID = %d)\n", pid);
        
        // Send 5 signals
        for(int i = 0; i < 5; i++) {
            sleep(1);  // Demonstrative delay
            kill(pid, SIGUSR1);
        }

        // Wait for child to finish
        wait(NULL);
        printf("Padre: Hijo terminado. Saliendo...\n");
    }

    return EXIT_SUCCESS;
}
