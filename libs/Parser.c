#include "Token.h"
#include "tSimbolos.h"
#include "tokenizer.c"
#include <stdio.h>

//escribir
void operando(){
	switch (token.type) {
		case NUM:
			printf("%s", token.value);
			analex();
		break;
		case IDT:{
			int pos = atoi(token.value);
			//-1 variable no def
			printf("%f", tsGetValPos(pos));
			analex();
		}
		break;
		default:
			printf("Error in Line: %d, Se esperaba: [NUM, IDT] y se encontro %s\n", calcLine(), getToken(token));
			//exit(1);
		break;
	}
}
void expr(){
	//expr -> Operando | expr1
	operando();
}
void tipoOpcion(){
	// tipoOpcion -> expr | cad | idt
	expr();
	switch (token.type) {
		case CAD:
		case NUM:
			printf("%s", token.value);
			analex();
		break;
		case IDT:{
			int pos = atoi(token.value);
			printf("%f", tsGetValPos(pos));
			analex();
		}
		break;
		default:
		break;
	}
}
void escribir(){
	// Escribir -> ESC ( tipoOpcion Opcion ) 
	analex();
	if (token.type == PAP) {
		analex();
		tipoOpcion();
		if (token.type == PCI ) {
			analex();
		}else {
			printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLine(), getToken(token));
			exit(1);
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}
//fin escribir
//lectura
void masId(){
	// masId -> , ID masId | Lamba
	analex();
	if(token.type == COM){
		analex();
		if(token.type == IDT){
			double x;
			scanf("%lf", &x);
			int pos = atoi(token.value);
			tsSetValPos(pos, x);
			masId();
		}else {
			printf("Error in Line: %d, Se esperaba: [IDT] y se encontro %s\n", calcLine(), getToken(token));
			exit(1);
		}
	}
}
void lectura(){
	// Lectura -> LEE ( ID masId)
	analex();
	if(token.type == PAP){
		analex();
		if(token.type == IDT){
			double x;
			scanf("%lf", &x);
			int pos = atoi(token.value);
			tsSetValPos(pos, x);
			masId();
			if(token.type == PCI){
				analex();
			}else {
				printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLine(), getToken(token));
				exit(1);
			}
		}else{
			printf("Error in Line: %d, Se esperaba: [IDT] y se encontro %s\n", calcLine(), getToken(token));
			exit(1);
		}
	}else{
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}
// fin lectura
void sentencia(){
	// Sentencia -> Lectura | Escribir | Condicional | salto | asignacion
	switch (token.type) {
		case LEE:
			lectura();
			break;
		case ESC:
			escribir();
			break;
		case SI_:
			break;
		case IRA:
			break;
		case IDT:
			break;
		default:
			printf("Error in Line: %d, Se esperaba: [idt, leer, escribir, ir_a, si] y se encontro %s\n", calcLine(), getToken(token));
			exit(1);
			break;
	}
}
void codigo(){
	// Codigo -> Sentencia Codigo | Lamba
	analex();
	//debug
	/*
	printf(" %s ",getToken(token));
	if(getChar()=='\n')
		printf("\n");
	if(getChar()=='\t')
		printf("\t");
	*/
	if(token.type == LEE ||
		token.type == ESC ||
		token.type == SI_ ||
		token.type == IRA ||
		token.type == IDT){
		sentencia();
		codigo();
	}
	//si no lamba
}

void iniciar(Reader *reader) { 
	codigo();
	tsPrint();
	/*
	while (list!=NULL) {
		printf("%s\n", getToken(list->tk));
		list=list->sig;
	}*/
}
