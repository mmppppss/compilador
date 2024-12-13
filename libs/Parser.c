#include "Token.h"
#include "reader.h"
#include "tSimbolos.h"
#include "tokenizer.c"
#include <stdio.h>

int ope = 0;
double operando1;
tokenType toperador;
double operando2;
double resultado;
bool isValid(tokenType tt) {
	switch (tt) {
		case LEE:
		case ESC:
		case IDT:
		case SI_:
		case IRA:
			return true;
		break;
		default:
			return false;
	}
}

void limpiar(){
	ope = 0;
	operando1 = 0;
	operando2 = 0;
	toperador = 0;
	resultado = 0;
}

void salto(){
	//salt -> ir_a num
	analex();
	if(token.type==NUM){
		int num = atoi(token.value);
		irAlinea(num);
	}else {
		printf("Error in Line: %d, Se esperaba: \"NUM\" y se encontro %s\n", calcLine(), getToken(token));
	}
}
//expresion
void operando(){
	//operando -> IDT | NUM
	printf("entrando a operando\n");
	double num;
	if(token.type==IDT){
		int pos = atoi(token.value);
		num = tsGetValPos(pos);
	}else if(token.type==NUM){
		num = atof(token.value);
	}else {
		printf("Error in Line: %d, Se esperaba: NUM o IDT y se encontro %s\n", calcLine(), getToken(token));
	}
	if(ope == 0){
		operando1 = num;
		ope = 1;
	}else{
		operando2 = num;
		ope = 0;
	}
	printf("saliendo de operando\n");
	analex();
}
void operador(){
	//operador -> SUM | RES | MUL | DIV
	if(token.type==SUM || token.type==RES || token.type==MUL || token.type==DIV){
		toperador = token.type;
	}
	printf("saliendo de operador\n");
	analex();
}
void expresion(){
	//expresion -> Operando Expr1()
	//printf("entrando a expresion\n");
	limpiar();
	operando();
	printf("operando 1: %f\n", operando1);
	printf("\ne1 token actual: %s\n", getToken(token));
	if(token.type == SUM || token.type == RES || token.type == MUL || token.type == DIV){
		operador();
		printf("\ne2token actual: %s\n", getToken(token));
		operando();
		printf("\ne3token actual: %s\n", getToken(token));
		switch (toperador) {
			case SUM:
				resultado = operando1 + operando2;
			break;
			case RES:
				resultado = operando1 - operando2;
			break;
			case MUL:
				resultado = operando1 * operando2;
			break;
			case DIV:
				resultado = operando1 / operando2;
			break;
		}

	}else {
		printf("e6 token actual: %s\n", getToken(token));
		resultado = operando1;
	}
	//printf("saliendo de expresion\n");
}
//fin expresion

//asignacion
void asignacion(){
	//asignacion -> IDT = expresion
	tsPrint();
	int pos = atoi(token.value);
	printf("entrando a asignacion, pos: %d\n", pos);
	analex();
	if(token.type==ASG){
		analex();
		expresion();
		/*
		if(token.type == NUM){
			resultado = atof(token.value);
			tsSetValPos(pos, resultado);
		}*/
		tsSetValPos(pos, resultado);
	}else {
		printf("Error in Line: %d, Se esperaba: \"ASG\" y se encontro %s\n", calcLine(), getToken(token));
	}
}
//fin asignacion


//escritura
void tipoOpcion(){
	if(token.type==CAD){
		printf("%s",token.value);
		analex();
	}else {
		expresion();
		//printf("\nes token actual: %s\n", getToken(token));
		printf("%lf", resultado);
	}
}
void Opcion(){
	// Opcion -> , tipoOpcion Opcion() | lambda
	if(token.type==COM){
		analex();//tk ,
		tipoOpcion();
		//printf("\nop token actual: %s\n", getToken(token));
		Opcion();
		printf("\n");
	}else {
		//printf("saliendo de Opcion\n");
	}
}
void salida(){
	//salida -> escribir(tipoOpcion Opcion)
	//printf("entrando a escribir\n");
	analex();//tk escribir
	if(token.type==PAP){
		analex();//tk pap
		tipoOpcion();
		//analex();
		Opcion();
		if(token.type==PCI){
			//printf("saliendo de escribir\n");
		}else {
			//printf("\nsa token actual: %s\n", getToken(token));
			printf("*Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLine(), getToken(token));
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLine(), getToken(token));
	}
}
//fin escribir
//lectura
void masID(){
	//masID -> ,ID masID() | lambda
	//printf("entrando a masID\n");
	analex();
	if(token.type==COM){
		analex();
		if(token.type==IDT){
			double numero;
			scanf("%lf", &numero);
			int pos = atoi(token.value);
			tsSetValPos(pos, numero);
			masID();
		}else {
			printf("Error in Line: %d, Se esperaba: \"IDT\" y se encontro %s\n", calcLine(), getToken(token));
		}
	}else {
		//printf("saliendo de masID\n");
	}
}
void lectura(){
	//lectura -> leer(ID masID())
	//printf("entrando a lectura\n");
	analex();
	if(token.type==PAP){
		analex();
		if(token.type==IDT){
			double numero;
			scanf("%lf", &numero);
			int pos = atoi(token.value);
			tsSetValPos(pos, numero);
			//imple masID
			masID();
			if(token.type==PCI){
				//analex();
				//printf("saliendo de lectura\n");
			}else {
				printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLine(), getToken(token));
			}
		}else{
			printf("Error in Line: %d, Se esperaba: \"IDT\" y se encontro %s\n", calcLine(), getToken(token));
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLine(), getToken(token));
	}
}
//fin lectura
void sentencia(){
	//sentencia -> lee | escribir | ir_a | si | idt
	switch (token.type) {
		case LEE:
			lectura();
		break;
		case ESC:
			salida();
		break;
		case IRA:
			salto();	
		break;
		case SI_:
			printf("ir a si_\n");
		break;
		case IDT:
			asignacion();
		break;
		default:
			printf("error\n");
		break;
	
	}
}

void codigo() {
	//codigo -> sentencia codigo | lambda
	//printf("entrando a codigo\n");
	analex();
	//printf("token: %s", getToken(token));
	if (isValid(token.type)) {
		//printf("entrando a sentencia\n");
		sentencia();
		codigo();
	}
	else {
		//printf("saliendo de codigo\n");
		return;
	}
}

void iniciar(Reader *reader) { 
	codigo();
	//printf("fin codigo()\n");
	tsPrint();
	/*
	while (list!=NULL) {
		printf("%s\n", getToken(list->tk));
		list=list->sig;
	}*/
}
