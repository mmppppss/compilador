#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"

Token createToken(tokenType type, char *value) {
    Token newToken;
	newToken.type = type;
    newToken.value = value;
    return newToken;
}
const char* tokenToString(tokenType t) {
    switch (t) {
        case NUM: return "NUM";
        case CAD: return "CAD";
        case SUM: return "SUM";
        case RES: return "RES";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case MYR: return "MYR";
        case MYI: return "MYI";
        case MNR: return "MNR";
        case MNI: return "MNI";
        case ASG: return "ASG";
        case IGU: return "IGU";
        case NOT: return "NOT";
        case DIF: return "DIF";
        case AND: return "AND";
        case OR_: return "OR";
        case IDT: return "IDT";
        case PAP: return "PAP";
        case PCI: return "PCI";
        case ERR: return "ERR";
		case LEE: return "LEE";
		case ESC: return "ESC";
		case IRA: return "IRA";
		case SI_: return "SI_";
		case ENT: return "ENT";
		case COM: return "COM";
		case FIN: return "FIN";
        default: return "UNKNOWN";
    }
}

char *getToken(Token token) {
    char *value = token.value;
	char *grn = "\033[32m";
	char *cln = "\033[0m";
    size_t length = snprintf(NULL, 0, "%s<%s%s:%s%s>%s", grn,cln, tokenToString(token.type), value, grn, cln) + 1;
    char *result = (char *)malloc(length);
    if (result == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
	sprintf(result,  "%s<%s%s:%s%s>%s", grn,cln, tokenToString(token.type), value, grn, cln);
    //sprintf(result, "<%s:%s>", tokenToString(token.type), value);
    return result;
}
