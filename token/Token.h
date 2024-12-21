
typedef enum{
	NUM,
	CAD,

	LEE,
	ESC,

	SUM,
	RES,
	MUL,
	DIV,
	MOD,

	MYR,
	MYI,
	MNR,
	MNI,
	IGU,
	DIF,
	
	IRA,

	SI_,
	ENT,
	FSI,

	ASG,
	IDT,
	PAP,
	PCI,
	COM,
	ERR,

	NOT, AND, OR_
}tokentype;

typedef struct {
	tokentype type;
    char *value;
} Token;

Token createToken(tokentype type, char *value);
char *getToken(Token token);
Token reservada(char *name);
