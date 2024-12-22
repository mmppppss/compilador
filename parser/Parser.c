#include "Parser.h"


int ope = 0;
double operando1;
tokentype toperador=ERR;
tokentype roperador=ERR;
double operando2;
double resultado;

Token token;
void iniciar(Reader *reader){
	analex();
	codigo();
	//imprimir tabla de simbolos
	//tsPrint();
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
			//condicional2();
			condicional();
		break;
		case IDT:
			asignacion();
		break;
		case FSI:
			analex();
			//lambda si es fin de si
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
			int pos = atoi(token.value);
			tsSetValPos(pos, numero);
			masID();
			if(token.type==PCI){
				analex();
			}else {
				printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLinea(), getToken(token));
				exit(1);
			}
		}else{
			printf("Error in Line: %d, Se esperaba: \"IDT\" y se encontro %s\n", calcLinea(), getToken(token));
			exit(1);
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLinea(), getToken(token));
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
			printf("Error in Line: %d, Se esperaba: \"IDT\" y se encontro %s\n", calcLinea(), getToken(token));
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
			printf("Error in Line: %d, Se esperaba: \")\" y se encontro %s\n", calcLinea(), getToken(token));
			exit(1);
		}
	}else {
		printf("Error in Line: %d, Se esperaba: \"(\" y se encontro %s\n", calcLinea(), getToken(token));
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
	limpiar();
	operando();
	expresion1();

	resultado = operando1;
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
				if(operando2 == 0){
					printf("Error in Line: %d, No se puede dividir entre 0\n", calcLinea());
					exit(1);
				}
				resultado = operando1 / operando2;
			break;
			case MOD:
				resultado = fmod(operando1, operando2);
			break;
		}
	}
}

void expresion1(){
	if(token.type == SUM || token.type == RES || token.type == MUL || token.type == DIV || token.type == MOD){
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
	}else if(token.type==NUM){
		num = atof(token.value);
	}else {
		printf("Error in Line: %d, Se esperaba: \"IDT\" o \"NUM\" y se encontro %s\n", calcLinea(), getToken(token));
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
	if(token.type==SUM || token.type==RES || token.type==MUL || token.type==DIV || token.type==MOD){
		toperador = token.type;
	}
	analex();
}

void salto(){
	//salto -> ir_a NUM
	analex();
	if(token.type==NUM){
		int num = atoi(token.value);
		irALinea(num);
		analex();
	}else {
		printf("Error in Line: %d, Se esperaba: \"NUM\" y se encontro %s\n", calcLinea(), getToken(token));
	}
}

void condicional(){
	//condicional -> si expresion opRelacional expresion entonces sentencia()
	analex();
	expresion();
	double res1 = resultado;
//	operadorRelacional();
	
	roperador = token.type;
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
			default:
				printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\", \"MENORIGUAL\", IGU, DIF y se encontro %s\n", calcLinea(), getToken(token));
			break;
		}
		if(cond){
			if(token.type==ENT){
				analex();
				sentencia();
			}else {
				printf("Error in Line: %d, Se esperaba: \"ENT\" y se encontro %s\n", calcLinea(), getToken(token));
				exit(1);
			}
		}else {
			while(token.type!=FSI){
				analex();
			}
			analex();//salta el FIN_SI
		}
	}else {
		printf("11Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" IGU DIF y se encontro %s\n", calcLinea(), getToken(token));
		exit(1);
	}
}

void condicional2() {
    // condicional -> si expresion opRelacional expresion entonces sentencia()
    analex();  // Avanzar al primer token
    expresion();  // Evaluar la primera expresión
    double res1 = resultado;

    // Validar el operador relacional
    if (token.type == MYR || token.type == MNR || token.type == MYI || 
        token.type == MNI || token.type == IGU || token.type == DIF) {
        
        tokentype roperador = token.type;  // Guardar operador relacional
        analex();  // Avanzar al siguiente token
        expresion();  // Evaluar la segunda expresión
        double res2 = resultado;

        bool cond = false;  // Evaluar la condición
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
            default:
                printf("Error in Line: %d, Operador relacional inválido: %s\n",
                       calcLinea(), getToken(token));
                exit(1);
        }

        if (cond) {
            // Si la condición se cumple, buscar "ENTONCES"
            if (token.type == ENT) {
                analex();  // Avanzar al token después de "ENTONCES"
                sentencia();  // Ejecutar una sola sentencia
            } else {
                printf("Error in Line: %d, Se esperaba \"ENTONCES\" y se encontró %s\n",
                       calcLinea(), getToken(token));
                exit(1);
            }
        } else {
            // Si la condición no se cumple, saltar a la línea siguiente
            int nextLine = calcLinea() + 1;  // Suponiendo que quieres saltar una línea
            irALinea(nextLine);
            analex();  // Avanzar al siguiente token
        }
    } else {
        printf("Error in Line: %d, Se esperaba un operador relacional válido y se encontró %s\n",
               calcLinea(), getToken(token));
        exit(1);
    }
}
void operadorRelacional(){
	//opRelacional -> MAYOR | MENOR | MAYORIGUAL | MENORIGUAL ==
	if(token.type==MYR || token.type==MNR || token.type==MYI || token.type==MNI || token.type==IGU || token.type==DIF){
		roperador = token.type;
	}else {
		roperador = ERR;
		printf("Error in Line: %d, Se esperaba: \"MAYOR\", \"MENOR\", \"MAYORIGUAL\" o \"MENORIGUAL\" y se encontro %s\n", calcLinea(), getToken(token));
		exit(1);
	}
}
void asignacion(){
	//asignacion -> IDT = expresion
	int pos = atoi(token.value);
	analex();
	if(token.type==ASG){
		analex();
		expresion();
		tsSetValPos(pos, resultado);
		//printf("Se asigno el valor: %f en la posicion: %d\n", resultado, pos);
	}else {
		printf("Error in Line: %d, Se esperaba: \"=\" y se encontro %s\n", calcLinea(), getToken(token));
		exit(1);
	}
}

//auxiliar

bool isValid(tokentype tt){
	switch (tt) {
		case LEE:
		case ESC:
		case IDT:
		case SI_:
		case IRA:
		case FSI:
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
	//roperador = ERR;
	resultado = 0;
}

