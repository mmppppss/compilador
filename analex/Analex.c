#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Analex.h"
Token token;

void analex() {
	char *ac = NULL;
	ac=(char *)malloc(1000*sizeof(char));
    if (ac == NULL) {
        fprintf(stderr, "Error al reservar memoria\n");
        exit(EXIT_FAILURE);
    }
    int peso = 0, estado = 0, count = 0;

	ac=concat("", '\0');
    for (;;) {
        char c = getCC();
		/* to debug
        printf("Analizando:%c\t\t", c);
		printf("estado: %d\t\t", estado);
		printf("acumlador: %s\n", ac);
		*/

        //if (c == EOF) 
        //w  break;
	
        switch (estado) {
			case -1:
				token = createToken(ERR, "End of File");
				return;
				break;
            case 0:
                if (c == ' ') {
                    avanzar(); // Ignorar espacios en blanco
                } else if(isdigit(c)) {
                	ac = concat(ac,c);//ac[sizeof(ac)]=c;
					estado=1;
					avanzar();
                }else if (c == '"') {
                	//ac = concat(ac,c);//ac[sizeof(ac)]=c; no concat ""
					estado=4;
					avanzar();
                } else if (c == '+') {
					estado=7;
					avanzar();
                } else if (c == '-') {
					estado=8;
					avanzar();
                } else if (c == '*') {
					estado=9;
					avanzar();
				} else if (c == '/') {
					estado=10;
					avanzar();
				} else if (c == '%') {
					estado=11;
					avanzar();
				} else if (c == '>') {
					estado=12;
					avanzar();
				} else if (c == '<') {
					estado=15;
					avanzar();
				} else if (c == '=') {
					estado=18;
					avanzar();
				} else if (c == '!') {
					estado=21;
					avanzar();
				} else if (c == '&') {
					estado=24;
					avanzar();
				} else if (c == '|') {
					estado=25;
					avanzar();
				} else if (isalpha(c)) {
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					estado=26;
					avanzar();
				} else if (c == '(') {
					estado=28;
					avanzar();
				} else if (c == ')') {
					estado=29;
					avanzar();
				} else if(c=='\0'){
					estado=-1;
					avanzar();//no usado
				} else if(c==','){
					estado=31;
					avanzar();	
				} else {
                	estado=0;
					//printf("deteccion no valida %c",c);
					avanzar();
                }
                break;
            case 1: // Estado de número
                if (isdigit(c)) {
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					
                    avanzar();
					//estado continua en 1
                } else if(c == '.') {
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					
					estado=3;
					avanzar();
                } else {
					estado=2;
                }
                break;
			case 2:{
					double num = atof(ac);
					token = createToken(NUM, ac);
					return;
				}
				break;
			case 3:
				if(isdigit(c)){
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					
					estado=3;
					avanzar();
				}else{
					estado=2; //adminte 3. 3.2 num con punto por delante 0 decimal
				}
				break;
			case 4:
				if(c=='\\'){
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					
					estado=5;
					avanzar();
				}else if(c=='"'){
					//ac = concat(ac,c);;//ac[sizeof(ac)]=c; no concat ""
					estado=6;
					avanzar();
				}else if (c=='\0') {
					estado=-1;
					avanzar();//no usado
				} else {
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					avanzar();
					//sigue en est 4
				}
				break;
			case 5:
				if (c=='\0') {
					estado=-1;
					avanzar();//no usado
				}else {
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					estado=4;
					avanzar();
				}
				break;
			case 6:
				token = createToken(CAD, ac);
				return;
				break;
			case 7:
				token = createToken(SUM, "_");
				return;
				break;
			case 8:
				token = createToken(RES, "_");
				return;
				break;
			case 9:
				token = createToken(MUL, "_");
				return;
				break;
			case 10:
				if(c=='/'){
					estado=30;
				}else{
					token = createToken(DIV, "_");
					return;
				}
				break;
			case 11:
				token = createToken(MOD, "_");
				return;
				break;
			case 12:
				if( c == '='){
					estado=14;
					avanzar();
				}else{
					estado=13;
				}
				break;
			case 13:
				token = createToken(MYR, "_");
				return;
				break;
			case 14:
				token = createToken(MYI, "_");
				return;
				break;
			case 15:
				if (c == '=') {
					estado = 17;
					avanzar();
				} else {
					estado = 16;
				}
				break;
			case 16:
				token = createToken(MNR, "_");
				return;
				break;
			case 17:
				token = createToken(MNI, "_");
				return;
				break;
			case 18:
				if (c == '=') {
					estado = 20;
					avanzar();
				} else {
					estado = 19;
				}
				break;
			case 19:
				token = createToken(ASG, "_");
				return;
				break;
			case 20:
				token = createToken(IGU, "_");
				return;
				break;
			case 21:
				if (c == '=') {
					estado = 23;
					avanzar();
				} else {
					estado = 22;
				}
				break;
			case 22:
				token = createToken(NOT, "_");
				return;
				break;
			case 23:
				token = createToken(DIF,"_");
				return;
				break;
			case 24:
				token = createToken(AND, "_");
				return;
				break;
			case 25:
				token = createToken(OR_, "_");
				return;
				break;
			case 26:
				if(isalpha(c) || isdigit(c) || c == '_'){
					ac = concat(ac,c);;//ac[sizeof(ac)]=c;
					
					estado=26;
					avanzar();
				}else{
					estado=27;
				}
				break;
			case 27:{
				Token tempToken = reservada(ac);	
				if(tempToken.type==IDT){
					//int posTS = tsInstall(ac, 0.0);
					//char str[20];
					char *str = malloc(20 * sizeof(char));
					snprintf(str, sizeof(str), "%d", 1);
					token = createToken(IDT, str);
				}else{
					token = tempToken;
				}
				return;}
				break;
			case 28:
				token = createToken(PAP, "_");
				return;
				break;
			case 29:
				token = createToken(PCI, "_");
				return;
				break;
			case 30:
				if(c=='\n'){
					estado=0;
					avanzar();
				}else{
					estado=30;
					avanzar();
				}
			break;
			case 31:
				token = createToken(COM, "_");
				return;
				break;
            default:
				printf("Deteccion no valida %c\n", c);
                break;
        }
    }
} 


void mostrarTokens(Reader *reader) { 
	while(reader->pos < reader->count-1){
		analex();

		//pushToken(&list, token);
		if(token.type!=ERR) {
			printf(" %s ",getToken(token));
			if(getCC()=='\n')
				printf("\n");
			if(getCC()=='\t')
				printf("\t");
		}
	}
	irALinea(1);
}
