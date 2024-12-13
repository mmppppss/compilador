// tSimbolos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSimbolos.h"

static tSimbolos tablaSimbolos;

void tsCrear(int capacidadInicial) {
    tablaSimbolos.simbolos = (tSimbolo*)malloc(capacidadInicial * sizeof(tSimbolo));
    tablaSimbolos.capacidad = capacidadInicial;
    tablaSimbolos.tamanio = 0;
}

void tsDestruir() {
    for (int i = 0; i < tablaSimbolos.tamanio; i++) {
        free(tablaSimbolos.simbolos[i].id);
    }
    free(tablaSimbolos.simbolos);
    tablaSimbolos.simbolos = NULL;
    tablaSimbolos.capacidad = 0;
    tablaSimbolos.tamanio = 0;
}

static void tsExpandir() {
    tablaSimbolos.capacidad *= 2;
    tablaSimbolos.simbolos = (tSimbolo*)realloc(tablaSimbolos.simbolos, tablaSimbolos.capacidad * sizeof(tSimbolo));
}

int tsInstall(char* id, double val) {
    if (tsExist(id)) {
        return tsGetPos(id); // Si ya existe, devuelve la posición.
    }
    if (tablaSimbolos.tamanio == tablaSimbolos.capacidad) {
        tsExpandir();
    }
    tablaSimbolos.simbolos[tablaSimbolos.tamanio].id = strdup(id);
    tablaSimbolos.simbolos[tablaSimbolos.tamanio].val = val;
    return tablaSimbolos.tamanio++;
}

double tsGetVal(char* id) {
    int pos = tsGetPos(id);
    if (pos != -1) {
        return tablaSimbolos.simbolos[pos].val;
    }
    fprintf(stderr, "Error: Símbolo '%s' no encontrado.\n", id);
    exit(EXIT_FAILURE);
}

double tsGetValPos(int pos) {
    if (pos >= 0 && pos < tablaSimbolos.tamanio) {
        return tablaSimbolos.simbolos[pos].val;
    }
    fprintf(stderr, "Error: Posición %d inválida.\n", pos);
    exit(EXIT_FAILURE);
}

bool tsExist(char* id) {
    return tsGetPos(id) != -1;
}

int tsSetVal(char* id, double val) {
    int pos = tsGetPos(id);
    if (pos != -1) {
        tablaSimbolos.simbolos[pos].val = val;
        return pos;
    }
    return tsInstall(id, val); // Si no existe, lo instala.
}

void tsSetValPos(int pos, double val) {
    if (pos >= 0 && pos < tablaSimbolos.tamanio) {
        tablaSimbolos.simbolos[pos].val = val;
    } else {
        fprintf(stderr, "Error: Posición %d inválida.\n", pos);
        exit(EXIT_FAILURE);
    }
}

int tsGetPos(char* id) {
    for (int i = 0; i < tablaSimbolos.tamanio; i++) {
        if (strcmp(tablaSimbolos.simbolos[i].id, id) == 0) {
            return i;
        }
    }
    return -1; // No encontrado.
}

void tsPrint() {
    printf("Tabla de símbolos:\n");
    for (int i = 0; i < tablaSimbolos.tamanio; i++) {
        printf("[%d] ID: %s, Valor: %.2f\n", i, tablaSimbolos.simbolos[i].id, tablaSimbolos.simbolos[i].val);
    }
}

