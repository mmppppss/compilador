#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libs/tokenizer.c"
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nombre_del_archivo>\n\tOptions: -s -v -t\n", argv[0]);
        return 1;
    }

	for (int i = 2; i < argc; i++) {
		char *opt= "-s";
		char *opt2= "-v";
		char *opt3= "-t";
		if(strcmp(argv[i],opt)==0){
			int *ln;
			printf("Mostrar linea x: ");
			scanf("%i", ln);
			printf("%s", getLine(*ln));
		}
		if(strcmp(argv[i],opt2)==0){
			show();
		}
		if(strcmp(argv[i],opt3)==0){
			start(argv[1]);
		}
	}


    return 0;
}

