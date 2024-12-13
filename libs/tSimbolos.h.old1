// tSimbolos.h
#ifndef TSIMBOLOS_H
#define TSIMBOLOS_H
#include <stdbool.h>

/**
 * Representación de un símbolo con ID y VALOR.
 */
typedef struct {
    char* id;
    double val;
} tSimbolo;

/**
 * Tabla de símbolos implementada como un vector dinámico.
 */
typedef struct {
    tSimbolo* simbolos;
    int capacidad;
    int tamanio;
} tSimbolos;

// Funciones para manejar la tabla de símbolos
void tsCrear(int capacidadInicial);
void tsDestruir();
int tsInstall(char* id, double val);
double tsGetVal(char* id);
double tsGetValPos(int pos);
bool tsExist(char* id);
int tsSetVal(char* id, double val);
void tsSetValPos(int pos, double val);
int tsGetPos(char* id);
void tsPrint();

#endif
