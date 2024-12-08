#include "tSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    install("x", 3.14);
    install("y", 2.718);
    install("z", 1.618);

    printf("¿Existe 'x'? %s\n", exist("x") ? "Sí" : "No");
    printf("¿Existe 'a'? %s\n", exist("a") ? "Sí" : "No");

    if (exist("x")) {
        printf("Valor de 'x': %.2f\n", getVal("x"));
    }

    setVal("x", 42.0);
    printf("Nuevo valor de 'x': %.2f\n", getVal("x"));

    install("x", 99.99);
    printf("Valor actualizado de 'x' después de install: %.2f\n", getVal("x"));

    if (!exist("w")) {
        printf("El símbolo 'w' no está en la tabla.\n");
    }

    return 0;
}
