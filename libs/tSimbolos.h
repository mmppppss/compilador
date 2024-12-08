#ifndef TSIMBOLOS_H
#define TSIMBOLOS_H
#include <stdbool.h>
/**
 *
 * | ID | VALOR |
 * |----|-------|    
 *
 */
typedef struct tSimbolos{
	char* id;
	double val;
	struct tSimbolos* sig;
}tSimbolos;

typedef tSimbolos* tSimbolo;
void tsInstall(char* id, double val);
double tsGetVal(char* id);
bool tsExist(char* id);
void tsSetVal(char* id, double val);
char* tsGetId(); //para obtener el ultimo solo para pruebas
void tsPrint();
#endif
