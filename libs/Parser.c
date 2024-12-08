#include "Token.h"
#include "tokenizer.c"

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

void sentencia(){
	// Sentencia -> Lectura | Escribir | Condicional | salto | asignacion
	switch (token.type) {
		case LEE:
			lectura();
			break;
		case ESC:
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
	printf(" %s ",getToken(token));
	if(getChar()=='\n')
		printf("\n");
	if(getChar()=='\t')
		printf("\t");

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
