#include "Token.h"
#include "reader.h"
#include "tSimbolos.h"
#include "tokenizer.c"
#include "Parser.h"
#include <stdbool.h>
#include <stdio.h>


int ope = 0;
double operando1;
tokenType toperador=ERR;
tokenType roperador=ERR;
double operando2;
double resultado;

void iniciar(Reader *reader){
	analex();
	codigo();
	//imprimir tabla de simbolos
	tsPrint();
}

void codigo(){
	//codigo -> sentencia codigo | lambda
	if(isValid(token.type)){
		sentencia();
		codigo();
	}

}
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
			condicional();
		break;
		case IDT:
			asignacion();
		break;
		default:
			printf("error\n");
		break;
	}
}


void lectura(){
	//lectura -> leer(ID masID)
	analex();
	if(token.type==PAP){
		analex();
		if(token.type==IDT){
			double numero;
			scanf("%lf", &numero);
			//printf("Se leyo el valor: %lf\n", numero);
			int pos = atoi(token.value);
			//printf("pos para el valor: %d\n", pos);
			tsSetValPos(pos, numero);
			masID();
			if(token.type==PCI){
				analex();
			}else {
				printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLine(), getToken(token));
				exit(1);
			}
		}else{
			printf("Error in Line: %d, Se esperaba: \"IDT\" y se encontro %s\n", calcLine(), getToken(token));
			exit(1);
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}

void masID(){
	//masID -> , ID masID | lambda
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
			exit(1);
		}
	}//lambda
}

void salida(){
	//salida -> escribir(tipoOpcion Opcion)
	analex();
	if(token.type==PAP){
		analex();
		tipoOpcion();
		Opcion();
		if(token.type==PCI){
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

void tipoOpcion(){
	//tipoOpcion -> CAD | Expresion
	if(token.type==CAD){
		printf("%s\n",token.value);
		analex();
	}else {
		expresion();
		printf("%lf\n", resultado);
	}
}
void Opcion(){
	// Opcion -> , tipoOpcion Opcion() | lambda
	if(token.type==COM){
		analex();
		tipoOpcion();
		Opcion();
	}//lambda
}

void expresion(){
	//expresion -> operando operador operando
	//limpiar();
	printf("\n");
	tsPrint();
	printf("\n");
	operando();
	expresion1();
	if(toperador != ERR){
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
		resultado = operando1;
	}
}

void expresion1(){
	if(token.type == SUM || token.type == RES || token.type == MUL || token.type == DIV){
		operador();
		operando();
	}
}

void operando(){
	//operando -> IDT | NUM
	double num;
	if(token.type==IDT){
		int pos = atoi(token.value);
		num = tsGetValPos(pos);
		printf("op1Se obtuvo el valor: %lf de la posicion: %d\n", num, pos);
	}else if(token.type==NUM){
		num = atof(token.value);
		printf("opSe obtuvo el valor: %lf\n", num);
	}else {
		printf("Error in Line: %d, Se esperaba: \"IDT\" o \"NUM\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
	if(ope == 0){
		operando1 = num;
		ope = 1;
	}else{
		operando2 = num;
		ope = 0;
	}
	analex();
}

void operador(){
	//operador -> SUM | RES | MUL | DIV
	if(token.type==SUM || token.type==RES || token.type==MUL || token.type==DIV){
		toperador = token.type;
	}
	analex();
}

void salto(){
	//salto -> ir_a NUM
	analex();
	if(token.type==NUM){
		int num = atoi(token.value);
		irAlinea(num);
	}else {
		printf("Error in Line: %d, Se esperaba: \"NUM\" y se encontro %s\n", calcLine(), getToken(token));
	}
}

void condicional(){
	//condicional -> si expresion opRelacional expresion entonces sentencia()
	analex();
	expresion();
	double res1 = resultado;
//	operadorRelacional();
	if(token.type==MYR || token.type==MNR || token.type==MYI || token.type==MNI || token.type==IGU || token.type==DIF){
		roperador = token.type;
		analex();
		expresion();
		double res2 = resultado;
		bool cond = false;
		switch (roperador) {
			case MYR:
				cond = res1 > res2;
			break;
			case MNR:
				cond = res1 < res2;
			break;
			case MYI:
				cond = res1 >= res2;
			break;
			case MNI:
				cond = res1 <= res2;
			break;
			case IGU:
				cond = res1 == res2;
			break;
			case DIF:
				cond = res1 != res2;
			break;
		}
		if(cond){
			if(token.type==ENT){
				analex();
				sentencia();
			}else {
				printf("Error in Line: %d, Se esperaba: \"ENT\" y se encontro %s\n", calcLine(), getToken(token));
				exit(1);
			}
		}else {
			while(token.type!=FIN){
				analex();
			}
			analex();
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}
void operadorRelacional(){
	//opRelacional -> MAYOR | MENOR | MAYORIGUAL | MENORIGUAL ==
	if(token.type==MYR || token.type==MNR || token.type==MYI || token.type==MNI || token.type==IGU || token.type==DIF){
		roperador = token.type;
	}else {
		roperador = ERR;
		printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}
void asignacion(){
	//asignacion -> IDT = expresion
	analex();
	if(token.type==ASG){
		printf("asignacion: %s\n", token.value);
		analex();
		printf("token: %s\n", getToken(token));
		expresion();
		printf("token: %s\n", getToken(token));

		int pos = atoi(token.value);
		printf("pos: %d\n", pos);
		tsSetValPos(pos, resultado);
		printf("resultado: %f\n", resultado);
		//printf("Se asigno el valor: %f en la posicion: %d\n", resultado, pos);
	}else {
		printf("Error in Line: %d, Se esperaba: \":=\" y se encontro %s\n", calcLine(), getToken(token));
		exit(1);
	}
}

//auxiliar

bool isValid(tokenType tt){
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
	toperador = ERR;
	roperador = ERR;
	resultado = 0;
}

