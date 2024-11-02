#include "Token.h"
#include "lTokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pushToken(lToken *list, Token tk){
	lToken aux = malloc(sizeof(lisToken));
	aux->tk=tk;
	aux->sig=NULL;
	/*if (*list==NULL) {
		*list=aux;
	}else{*/
	lToken temp=*list;
	while ((*temp).sig!=NULL) {
		temp=temp->sig;
	}
	temp->sig=aux;
	//}
}
Token popToken(lToken list){
	Token a=list->tk;
	list=list->sig;
	printf("exito2 popToken");
	return a;
}
