#include "Token.h"
#include "reader.h"
#include "tSimbolos.h"
#include "tokenizer.c"
#include "Parser.h"
#include <stdio.h>

int ope = 0;
double operando1;
tokenType toperador;
tokenType roperador;
double operando2;
double resultado;
bool isValid(tokenType tt) {
	/*printf("entrando a isValid\n");
	printf("tt: %d\n", tt);
	printf("%s\n", getToken(token));*/
	switch (tt) {
		case LEE:
		case ESC:
		case IDT:
		case SI_:
		case IRA:
		case FIN:
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
	//analex(); //esto lo puse en expresion para evitar un fallo de doble analex avance
}
void operador(){
	//operador -> SUM | RES | MUL | DIV
	if(token.type==SUM || token.type==RES || token.type==MUL || token.type==DIV){
		toperador = token.type;
	}
	analex();
}
void expresion1(){
	if(token.type == SUM || token.type == RES || token.type == MUL || token.type == DIV){
		operador();
		operando();
	}
}
void expresion(){
	//expresion -> Operando Expr1()
	//printf("entrando a expresion\n");
	limpiar();
	operando();
	analex();
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
	/*
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
	}*/
	//printf("saliendo de expresion\n");
}
//fin expresion

//condicional
void operadorRelacional(){
	//operadorRelacional -> MAYOR | MENOR | MAYORIGUAL | MENORIGUAL
	if(token.type==MYR || token.type==MNR || token.type==MYI || token.type==MNI){
		roperador = token.type;
	}else {
		printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" y se encontro %s\n", calcLine(), getToken(token));
	}
}

void condicional() {
	// condicional -> si expresion opRelacional expresion entonces sentencia();
	analex(); // Token "si"
	expresion(); // Evaluar la primera expresión
	double res1 = resultado; // Guardar el resultado de la primera expresión

	if (token.type == MYR || token.type == MNR || token.type == MYI || token.type == MNI || token.type == IGU) {
		// Si el token es uno de los operadores relacionales
		roperador = token.type;
		analex(); // Avanzar al siguiente token (esperando la segunda expresión)
		expresion(); // Evaluar la segunda expresión
		double res2 = resultado; // Guardar el resultado de la segunda expresión

		bool analizado = false;

		// Comparar las dos expresiones con el operador relacional
		switch (roperador) {
			case MYR:
				analizado = res1 > res2;
				break;
			case MNR:
				analizado = res1 < res2;
				break;
			case MYI:
				analizado = res1 >= res2;
				break;
			case MNI:
				analizado = res1 <= res2;
				break;
			case IGU:
				analizado = res1 == res2;
				break;
		}

		if (analizado) {
			// Si la condición es verdadera, proceder con la sentencia
			if (token.type == ENT) {
				analex(); // Token "ENTONCES"
				sentencia(); // Ejecutar la sentencia asociada
			} else {
				// Si no encontramos "ENTONCES", error
				printf("Error in Line: %d, Se esperaba: \"ENTONCES\" y se encontro %s\n", calcLine(), getToken(token));
			}
		} else {
			// Si la condición es falsa, saltar las sentencias hasta encontrar FIN
			while (token.type != FIN) {
				analex();
			}
		}
	} else {
		// Si no encontramos un operador relacional válido, mostrar error
		printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" y se encontro %s\n", calcLine(), getToken(token));
	}
}
//fin condicional

//asignacion
void asignacion(){
	//asignacion -> IDT = expresion
	int pos = atoi(token.value);
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
			condicional();
		break;
		case IDT:
			asignacion();
		break;
		case FIN:
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
	if(token.type == ERR) {
		return;
	}
	//printf("token: %s", getToken(token));
	if (isValid(token.type)) {
		//printf("entrando a sentencia\n");
		sentencia();
		codigo();
	}else {
		//printf("saliendo de codigo\n");
		printf("Error in Line: %d, Se esperaba: \"LEE\", \"ESC\", \"IRA\", \"SI_\", \"IDT\" y se encontro %s\n", calcLine(), getToken(token));
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
