
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
}token;

typedef struct {
	token type;
    char *value;
} Token;

Token createToken(token type, char *value);
char *getToken(Token token);
Token reservada(char *name);
