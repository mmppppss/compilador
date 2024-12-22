#ifndef ANALEX_H
#define ANALEX_H
#include "../token/Token.h"
#include "../reader/Reader.h"
#include "../simbolos/tSimbolos.h"


extern Token token;
void analex();
void mostrarTokens(Reader *reader);


#endif // ANALEX_H
