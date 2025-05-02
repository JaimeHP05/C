// Inclusión de bibliotecas necesarias
#include <stdio.h>      // Para funciones de entrada/salida estándar
#include <stdlib.h>     // Para exit() y otras funciones de utilidad
#include <unistd.h>     // Para fork() y otras llamadas al sistema
#include <sys/wait.h>   // Para wait()
#include <sys/types.h>  // Para tipos como pid_t
#include <sys/ipc.h>    // Para comunicación entre procesos (IPC)
#include <sys/shm.h>    // Para memoria compartida
#include <semaphore.h>  // Para semáforos POSIX

// Definición de constantes
#define NUM_HIJOS 3        // Número de procesos hijo a crear
#define ITERACIONES 100000 // Número de veces que cada hijo incrementará el contador

int main() {
    // Generación de clave única para la memoria compartida
    key_t clave = ftok("contador_mutex.c", 'R');

    // Creación del segmento de memoria compartida (contador + semáforo)
    int id_memoria = shmget(clave, 
                           sizeof(int) + sizeof(sem_t),  // Espacio para contador y semáforo
                           IPC_CREAT | 0666);

    // Obtención del puntero a la memoria compartida
    void *memoria_compartida = shmat(id_memoria, NULL, 0);
    
    // Configuración de punteros para contador y semáforo
    int *contador = (int*)memoria_compartida;                    // Inicio de la memoria
    sem_t *mutex = (sem_t*)(memoria_compartida + sizeof(int));  // Después del contador

    // Inicialización de variables compartidas
    *contador = 0;
    sem_init(mutex,  // Puntero al semáforo
             1,      // 1 = compartido entre procesos
             1);     // Valor inicial = 1 (desbloqueado)

    // Bucle de creación de procesos hijos
    for(int i = 0; i < NUM_HIJOS; i++) {
        if(fork() == 0) {  // Código ejecutado por cada proceso hijo
            // Cada hijo incrementa el contador ITERACIONES veces
            for(int j = 0; j < ITERACIONES; j++) {
                sem_wait(mutex);     // Entrada a sección crítica
                (*contador)++;       // Incremento protegido
                sem_post(mutex);     // Salida de sección crítica
            }
            // Desvinculación de la memoria compartida
            shmdt(memoria_compartida);
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
    sem_destroy(mutex);                    // Destruye el semáforo
    shmdt(memoria_compartida);             // Desvincula la memoria compartida
    shmctl(id_memoria, IPC_RMID, NULL);    // Marca la memoria para ser eliminada

    return 0;
}
