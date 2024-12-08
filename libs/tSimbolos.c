#include "tSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

tSimbolo tablaSimbolos;
void tsInstall(char* id, double val){
	if (tsExist(id)) {
		tsSetVal(id, val);
	}else{
        tSimbolo aux = malloc(sizeof(tSimbolos));
        aux->id = strdup(id); // Duplicar la cadena para evitar problemas de punteros
        aux->val = val;
        aux->sig = tablaSimbolos; // Insertar al inicio de la lista
        tablaSimbolos = aux;
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
void tsSetVal(char* id, double val){
	tSimbolo temp = tablaSimbolos;
	while (temp != NULL && strcmp(temp->id, id) != 0) {
		temp = temp->sig;
	}
	if (temp != NULL) {
		temp->val = val;
	}
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
