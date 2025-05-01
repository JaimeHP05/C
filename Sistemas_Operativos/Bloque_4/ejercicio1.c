// Inclusión de bibliotecas necesarias
#include <stdio.h>      // Para funciones de entrada/salida estándar
#include <stdlib.h>     // Para exit() y otras funciones de utilidad
#include <unistd.h>     // Para fork() y otras llamadas al sistema
#include <sys/wait.h>   // Para wait()
#include <sys/types.h>  // Para tipos como pid_t
#include <sys/ipc.h>    // Para comunicación entre procesos (IPC)
#include <sys/shm.h>    // Para memoria compartida

// Definición de constantes
#define NUM_HIJOS 3        // Número de procesos hijo a crear
#define ITERACIONES 100000 // Número de veces que cada hijo incrementará el contador

int main() {
    // Generación de clave única para la memoria compartida
    key_t clave = ftok("contador_carrera.c", 'R');  // Genera una clave única basada en el archivo

    // Creación del segmento de memoria compartida
    int id_memoria = shmget(clave,           // Clave generada
                           sizeof(int),       // Tamaño en bytes
                           IPC_CREAT | 0666); // Flags: crear si no existe | permisos rw-rw-rw-

    // Obtención del puntero a la memoria compartida
    int *contador = shmat(id_memoria,  // ID de la memoria compartida
                         NULL,         // Dirección específica (NULL = sistema decide)
                         0);           // Flags (0 = lectura/escritura)

    // Inicialización del contador
    *contador = 0;

    // Bucle de creación de procesos hijos
    for(int i = 0; i < NUM_HIJOS; i++) {
        if(fork() == 0) {  // Código ejecutado por cada proceso hijo
            // Cada hijo incrementa el contador ITERACIONES veces
            for(int j = 0; j < ITERACIONES; j++) {
                (*contador)++;  // Incremento sin protección -> condición de carrera
            }
            // Desvinculación de la memoria compartida
            shmdt(contador);
            exit(0);  // El hijo termina su ejecución
        }
    }

    // Código del proceso padre: espera a todos los hijos
    for(int i = 0; i < NUM_HIJOS; i++) {
        wait(NULL);  // Espera a que termine cualquier hijo
    }

    // Impresión de resultados
    printf("Valor final del contador: %d\n", *contador);
    printf("Valor esperado: %d\n", NUM_HIJOS * ITERACIONES);

    // Limpieza de recursos
    shmdt(contador);                    // Desvincula la memoria compartida
    shmctl(id_memoria, IPC_RMID, NULL); // Marca la memoria para ser eliminada

    return 0;
}
