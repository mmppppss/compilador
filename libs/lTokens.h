#ifndef LTOKENS_H
#define LTOKENS_H
#include "Token.h"

typedef struct lTokens{
	Token tk;
	struct lTokens *sig;
}lisToken;
typedef lisToken *lToken ;

//lToken list;
//lToken ult;
void pushToken(lToken *list, Token tk);//add to end of list
Token popToken(lToken list);//get and delete first 

#endif
