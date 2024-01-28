// Suma-Arreglo-En-Paralelo-A00260430.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

// Constantes
#define ELEMENTOS 2000  // M�ximo n�mero de elementos en los arreglos
#define PEDAZOS 200     // Tama�o de los pedazos de los arreglos a usar en la ejecuci�n paralela
#define MOSTRAR 20      // N�mero de elementos del arreglo a desplegar en la consola

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    // Definiendo arreglos con valores de punto flotante.
    float arr_a[ELEMENTOS], arr_b[ELEMENTOS], arr_c[ELEMENTOS], arr_v[ELEMENTOS];
    int subi;

    // Creando arreglos A y B con valores iniciales. Tambi�n se va a crear un arreglo de verificaci�n V
    for (subi = 0; subi < ELEMENTOS; subi++) {
        arr_a[subi] = subi * 10;
        arr_b[subi] = (subi + 3) * 3.7;
        // Creando arreglo de verificacion
        arr_v[subi] = arr_a[subi] + arr_b[subi];
    }

    int pedazos = PEDAZOS;

    // Definiendo los par�metros para la ejecuci�n en paralelo de la suma:
    // - Declarar como listas compartidas arr_a (arrego A), arr_b (arreglo B), arr_c (arreglo C) y pedazos usando
    //   la clausula shared
    // - Declarar como variable privada el contador subi usando la clausula private
    // - Indicar el tipo de distribuci�n de los pedazos de los arreglos y el tama�o de los pedazos del arreglo.
    //   El tipo de distribuci�n es est�tica y el tama�o de los pedazos est� determinado por la constante
    //   PEDAZOS 
    #pragma omp parallel for \
    shared (arr_a, arr_b, arr_c, pedazos) private (subi) \
    schedule(static, pedazos)
    // El estatuto for simple es la unica instrucci�n a ejecutar en el bloque paralelo 
    for (subi = 0; subi < ELEMENTOS; subi++)
        arr_c[subi] = arr_a[subi] + arr_b[subi];

    // Imprimiendo una muestra de valores para los arreglos
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo A: " << std::endl;
    imprimeArreglo(arr_a);
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo B: " << std::endl;
    imprimeArreglo(arr_b);
    std::cout << std::endl;
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo C: " << std::endl;
    imprimeArreglo(arr_c);
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo V: " << std::endl;
    imprimeArreglo(arr_v);

}

// Funci�n para desplegar datos en la consola. Despliega una l�nea con un n�mero predeterminado
// de elementos a mostrar definido en la constante MOSTRAR
void imprimeArreglo(float* d) {
    for (int subx = 0; subx < MOSTRAR; subx++) {
        std::cout << d[subx] << "-";
    }
    std::cout << std::endl;
}
