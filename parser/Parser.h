#ifndef PARSER_H
#define PARSER_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../analex/Analex.h"
#include "../reader/Reader.h"
#include "../simbolos/tSimbolos.h"

extern int ope;
extern double operando1;
extern tokentype toperador;
extern tokentype roperador;
extern double operando2;
extern double resultado;

bool isValid(tokentype tt);
void limpiar();
void salto();
void operando();
void operador();
void expresion1();
void expresion();
void operadorRelacional();
void condicional();
void condicional2();
void asignacion();
void tipoOpcion();
void Opcion();
void salida();
void masID();
void lectura();
void sentencia();
void codigo();
void iniciar(Reader *reader);

#endif /* ifndef PARSER_H */
