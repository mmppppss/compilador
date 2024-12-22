#ifndef TSIMBOLOS_H
#define TSIMBOLOS_H

#include <stdbool.h>
typedef struct tSimbolos{
	char* id;
	double val;
	struct tSimbolos* sig;
}tSimbolos;

typedef tSimbolos* tSimbolo;
int tsInstall(char* id, double val);
double tsGetVal(char* id);
double tsGetValPos(int pos);
bool tsExist(char* id);
int tsSetVal(char* id, double val);
void tsSetValPos(int pos, double val);
int tsGetPos(char* id);
char* tsGetId(); //para obtener el ultimo solo para pruebas
void tsPrint();

#endif // TSIMBOLOS_H
