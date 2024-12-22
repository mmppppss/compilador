#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "Reader.h"
Reader reader;

Reader *newReader(char *filename){
	reader.filename = filename;
	reader.content = NULL;
	reader.size = getSize();
	reader.lines = NULL;
	reader.countlines = 0;
	reader.pos = 0;
	reader.count = 0;
	loadFile();
	return &reader;
}

int getSize(){
	struct stat st;
	stat(reader.filename, &st);
	return st.st_size;
}

void loadFile() {
    FILE *f;
    f = fopen(reader.filename, "r");
    
    if (f == NULL) {
        printf("[ERROR1] No se pudo abrir el archivo %s\n", reader.filename);
        exit(1);
    }

    char c;
    reader.count = 0;
    reader.countlines = 0;
    reader.lines = (int *)malloc(sizeof(int) * 100); // Inicialmente asignar memoria para 100 líneas
    if (reader.lines == NULL) {
        printf("[ERROR2] No se pudo asignar memoria para lines\n");
        fclose(f);
        exit(1);
    }
    reader.lines[reader.countlines++] = 0;
    reader.content = (char *)malloc(sizeof(char) * reader.size);
    if (reader.content == NULL) {
        printf("[ERROR3] No se pudo asignar memoria para content\n");
        fclose(f);
        exit(1);
    }

    while ((c = fgetc(f)) != EOF) {
        if (reader.count >= reader.size - 1) {
            reader.size *= 2;
            char *temp = realloc(reader.content, sizeof(char) * reader.size);
            if (temp == NULL) {
                printf("[ERROR4] No se pudo reasignar memoria para content\n");
                fclose(f);
                exit(1);
            }
            reader.content = temp;
        }
        
        if (c == '\n') {
            if (reader.countlines >= 100) {
                int *temp = realloc(reader.lines, sizeof(int) * (reader.countlines + 100));
                if (temp == NULL) {
                    printf("[ERROR5] No se pudo reasignar memoria para lines\n");
                    fclose(f);
                    exit(1);
                }
                reader.lines = temp;
            }
            reader.lines[reader.countlines++] = reader.count + 1;
        }
        reader.content[reader.count++] = c;
    }
    reader.content[reader.count] = '\0';
    fclose(f);
}
void mostrar(){
	printf("%s", reader.content);
}

void mostrarCodigo(){
	char *bar = "\033[32m|";
	int ccc=1;
	printf("%i\t",ccc++);
	for (int i = 0; i < reader.count-1 ; i++) {
		printf("%s\033[0m%c", bar, reader.content[i]);
		if(reader.content[i]=='\n'){
			printf("%i\t", ccc++);
		}
	}
	printf("\033[0m\n");
}

void avanzar(){
	reader.pos++;
}
char getCC(){
	return reader.content[reader.pos];
}

int calcLinea(){
	int i=0;
	for(int j=0; j<reader.countlines; j++){
		if(reader.lines[j]>= reader.pos){
			return i+1;
		}else{
			i++;
		}
	}
	return i;
}
void irALinea(int linea){
    if (linea > 0 && linea <= reader.countlines) {
        reader.pos = reader.lines[linea - 1];
    } else {
        printf("[ERROR2]: salto a linea inexistente.\n");
    }
}


char* concat(char* s, char c) {
    size_t len = strlen(s);
    char* x = realloc(s, len + 2); // +1 para el carácter y +1 para el terminador nulo
    if (x == NULL) {
        fprintf(stderr, "Error al expandir memoria\n");
        exit(EXIT_FAILURE);
    }
    x[len] = c;
    x[len + 1] = '\0';
    return x;
}
