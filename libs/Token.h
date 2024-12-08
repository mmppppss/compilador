#ifndef TOKEN_H
#define TOKEN_H

#include <sys/types.h>
typedef enum {
	NUM,
	CAD,
	//cambiar por ART + * / -
	SUM,
	RES,
	MUL,
	DIV,
	MOD,
	//cambiar por LOG > < == 
	MYR,
	MYI,
	MNR,
	MNI,
	IGU,
	NOT,
	DIF,
	AND,
	OR_,
	ASG,
	IDT,
	PAP,
	PCI,
	ERR,
	LEE,
	ESC,
	IRA,
	SI_,
	ENT,
	COM
}tokenType;
/*typedef enum{
	LEE,
	ESC,
	IRA,
	SI_,
	ENT
}tokenReservadas;*/
typedef struct {
	tokenType type;
    char *value;
} Token;

Token createToken(tokenType type, char *value);
char *getToken(Token token);
#endif /* TOKEN_H */
