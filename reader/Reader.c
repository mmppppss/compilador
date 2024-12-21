#include "Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
Reader reader;

Reader *newReader(char *filename){
	reader.filename = filename;
	reader.content = NULL;
	reader.size = getSize();
	reader.lines = NULL;
	reader.countlines = 0;
	reader.pos = 0;
	reader.count = 0;
	return &reader;
}

int getSize(){
	struct stat st;
	stat(reader.filename, &st);
	return st.st_size;
}

void loadFile(){
	FILE *f;
	f = fopen(reader.filename, "r");
	
	if(f == NULL){
		printf("[ERROR1] No se pudo abrir el archivo %s\n", reader.filename);
		exit(1);
	}

	char c; 
	reader.lines = (int *)malloc(sizeof(int));
	reader.lines[reader.countlines++] = 0;
	reader.content = (char *)malloc(sizeof(char)*reader.size);
	while((c = fgetc(f)) != EOF){
		if(c == '\n'){
			reader.lines[reader.countlines++] = reader.count+1;
		}
		reader.content[reader.count++] = c;
	}
	reader.content[reader.count] = '\0';
	fclose(f);
}

void mostrar(){
	printf("%s", reader.content);
}

void avanzar(){
	reader.pos++;
}
char getCC(){
	return reader.content[reader.pos];
}
int calcLinea();
void irALinea(int linea);
