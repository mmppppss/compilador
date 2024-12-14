#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "reader.h"
#include "tSimbolos.h"

extern int ope;
extern double operando1;
extern tokenType toperador;
extern tokenType roperador;
extern double operando2;
extern double resultado;

bool isValid(tokenType tt);
void limpiar();
void salto();
void operando();
void operador();
void expresion1();
void expresion();
void operadorRelacional();
void condicional();
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
