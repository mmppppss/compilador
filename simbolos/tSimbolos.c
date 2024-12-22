#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tSimbolos.h"

tSimbolo tablaSimbolos = NULL;


int tsInstall(char* id, double val){
	if (tsExist(id)) {
		//printf("El símbolo '%s' con VALOR %.2f ya está en la tabla., asignando VALOR %.2f\n", id, tsGetVal(id), val);
		return tsGetPos(id);
	}else{
        tSimbolo aux = malloc(sizeof(tSimbolos));
		if (aux == NULL) {
    		fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo símbolo.\n");
    		exit(EXIT_FAILURE);
		}
        aux->id = strdup(id); // Duplicar la cadena para evitar problemas de punteros
        if (aux->id == NULL) {
    		fprintf(stderr, "Error: No se pudo duplicar la cadena.\n");
		    free(aux);
    		exit(EXIT_FAILURE);
		}
		aux->val = val;
        aux->sig = tablaSimbolos; // Insertar al inicio de la lista
        tablaSimbolos = aux;
		free(aux);
		return 0;
	}
}

double tsGetVal(char* id){
    tSimbolo temp = tablaSimbolos;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return temp->val; 
        }
        temp = temp->sig;
    }
    printf("Error: El símbolo '%s' no está en la tabla.\n", id);
    return 0.0; 
}

double tsGetValPos(int pos){
	tSimbolo temp = tablaSimbolos;
	int i = 0;
	while (temp != NULL) {
		if (i == pos) {
			return temp->val;
		}
		temp = temp->sig;
		i++;
	}
	return 0.0;
}
bool tsExist(char* id){
	tSimbolo temp = tablaSimbolos;
	while (temp != NULL) {
		if (strcmp(temp->id, id) == 0) {
			return true;
		}
		temp = temp->sig;
	}
	return false;
}
int tsSetVal(char* id, double val){
	tSimbolo temp = tablaSimbolos;
	int pos = 0;
	
	while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            temp->val = val;
            return pos; 
        }
        temp = temp->sig;
        pos++;
    }
	return -1;
}
int tsGetPos(char* id){
	tSimbolo temp = tablaSimbolos;
	int pos = 0;
	
	while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return pos; 
        }
        temp = temp->sig;
        pos++;
    }
	return -1;
}

void tsPrint(){
	tSimbolo temp = tablaSimbolos;
	printf("\tID\t\tVALOR\n");
	while (temp != NULL) {
		printf("\t%s\t|\t%f\t\n", temp->id, temp->val);
		temp = temp->sig;
	}
}
char* tsGetId(){
	return tablaSimbolos->id;
}

void tsSetValPos(int pos, double val){
	tSimbolo temp = tablaSimbolos;
	int i = 0;
	while (temp != NULL) {
		if (i == pos) {
			temp->val = val;
			return;
		}
		temp = temp->sig;
		i++;
	}
}
