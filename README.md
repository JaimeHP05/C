## Cómo usar este repositorio

1. **Clonar el repositorio:**
   ```bash
   git clone <https://github.com/JaimeHP05/C.git>

2. **Ejecutar los scripts:**
   ```bash
   cd C
   cd ASIGNATURA
   cd Bloque_X
   gcc -o  [El_nombre_que_quieras] ejercicioX.c
   ./[El_nombre_de_antes]


# Sistemas Operativos

Este repositorio contiene una colección de ejercicios prácticos implementados en C, diseñados para aprender y practicar conceptos fundamentales de programación de sistemas operativos, concurrencia, procesos, señales, hebras y sincronización. Cada bloque de ejercicios aborda un tema específico.


### Bloque 1: Procesos y Señales
Este bloque introduce el concepto de procesos en sistemas operativos, cómo crearlos, gestionarlos y comunicarse con ellos. Además, explora el manejo de señales en procesos y cómo utilizarlas para comunicación y control.


- **Ejercicio 1:** Crear una jerarquía de procesos en abanico, donde cada proceso hijo imprime su ID y el de su padre, y el padre espera la finalización de sus hijos.
  
- **Ejercicio 2:** Crear una jerarquía de procesos en forma de árbol, con los hijos imprimiendo su ID y el de su padre.
  
- **Ejercicio 3:** Crear N procesos que esperan un tiempo proporcional a su orden de creación antes de finalizar, mientras el padre gestiona su creación y finalización.
  
- **Ejercicio 4:** Crear dos procesos hijos, uno que abre una calculadora y otro que abre un editor de texto con varios archivos, utilizando funciones `exec()`.
  
- **Ejercicio 5:** Calcular el factorial de un número en un programa y usarlo en otro programa para calcular factoriales en paralelo con procesos hijos.
  
- **Ejercicio 6:** Explorar el uso de variables globales en procesos y la necesidad de memoria compartida para sincronización.
  
- **Ejercicio 7:** Capturar señales de alarma y gestionar su comportamiento en un bucle infinito con finalización controlada.

- **Ejercicio 8:** Enviar señales personalizadas entre un proceso padre e hijo, utilizando `signal()` y `kill()`.

- **Ejercicio 9:** Crear un programa que capture señales SIGUSR1 y otro que las envíe, seguido de una señal de terminación.



### Bloque 2: Hebras
Este bloque introduce el uso de hebras (threads) para realizar tareas concurrentes y gestionar recursos compartidos.


- **Ejercicio 1:** Crear N hebras que generan números aleatorios y devuelven sus sumas parciales al hilo principal.

- **Ejercicio 2:** Contar las líneas de múltiples archivos de texto en paralelo, utilizando una hebra por archivo.

- **Ejercicio 3:** Dividir un vector entre hebras para calcular la suma de sus elementos en paralelo.

- **Ejercicio 4:** Explorar problemas de concurrencia al incrementar una variable global desde múltiples hebras.



### Bloque 3: Hebras y Sincronización
Este bloque aborda la sincronización entre hebras utilizando semáforos binarios y generales.


- **Ejercicio 1:** Simular un sistema de clientes y proveedores que gestionan el stock de camisetas en una tienda, utilizando semáforos binarios.

- **Ejercicio 2:** Crear N hebras que generan números aleatorios y los suman a variables compartidas según su índice de creación (par o impar).

- **Ejercicio 3:** Implementar el problema del productor-consumidor con un buffer limitado, utilizando semáforos generales.

- **Ejercicio 4:** Sincronizar dos hebras para alternar la impresión de caracteres "A" y "B" en la salida estándar.



### Bloque 4: Memoria Compartida
Este bloque introduce el uso de memoria compartida entre procesos y cómo sincronizar su acceso.


- **Ejercicio 1:** Crear N procesos que comparten una variable en memoria compartida y la incrementan en paralelo.
  
- **Ejercicio 2:** Modificar el ejercicio anterior para garantizar exclusión mutua en el acceso a la variable compartida, utilizando semáforos generales.
