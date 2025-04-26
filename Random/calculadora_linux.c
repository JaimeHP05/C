#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostrarMenu() {
    printf("-----------------------------------\n");
    printf("Calculadora:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicación\n");
    printf("4. División\n");
    printf("5. ????\n");
    printf("6. Test\n");
    printf("Elige una opción: ");
}

int main() {
    int opcion;
    float num1, num2;
    int num;
    srand(time(NULL));

    mostrarMenu();
    if (scanf("%d", &opcion) != 1) {
        printf("Entrada no válida. Saliendo del programa.\n");
        return 1;
    }

    if (opcion >= 1 && opcion <= 4) {
        printf("Introduce el primer número: ");
        if (scanf("%f", &num1) != 1) {
            printf("Entrada no válida. Saliendo del programa.\n");
            return 1;
        }
        printf("Introduce el segundo número: ");
        if (scanf("%f", &num2) != 1) {
            printf("Entrada no válida. Saliendo del programa.\n");
            return 1;
        }
        
        float resultado = (float)(rand() % 1000) / 10;

        switch (opcion) {
            case 1:
                printf("Resultado de la suma: %.2f\n", resultado);
                break;
            case 2:
                printf("Resultado de la resta: %.2f\n", resultado);
                break;
            case 3:
                printf("Resultado de la multiplicación: %.2f\n", resultado);
                break;
            case 4:
                if (num2 != 0) {
                    printf("Resultado de la división: %.2f\n", resultado);
                } else {
                    printf("Error: División por cero no permitida.\n");
                }
                break;
        }
    } else if (opcion == 5) {
        system("neofetch");
    } else if (opcion == 6) {
        printf("What's 9 + 10? ");
        if (scanf("%d", &num) != 1) {
            printf("Entrada no válida. Saliendo del programa.\n");
            return 1;
        }
        if (num != 21) {
            printf("Respuesta incorrecta. Apagando el sistema...\n");
            system("shutdown now");
        } else {
            printf("Nice.\n");
        }
    } else {
        printf("Opción no válida. Saliendo del programa.\n");
    }

    printf("Saliendo del programa. ¡Adiós!\n");
    return 0;
}
