#ifndef TOKEN_H
#define TOKEN_H

#include <sys/types.h>
typedef enum {
	NUM,
	CAD,
	SUM,
	RES,
	MUL,
	DIV,
	MOD,
	MYR,
	MYI,
	MNR,
	MNI,
	ASG,
	IGU,
	NOT,
	DIF,
	AND,
	OR_,
	IDT,
	PAP,
	PCI,
	ERR,
	LEE,
	ESC,
	IRA,
	SI_,
	ENT
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
