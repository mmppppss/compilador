#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "reader.h"
Reader reader;

Reader *createReader(char *filename) {
	reader.filename = filename;
	reader.count = 0;
	reader.pos = 0;
	reader.countlines = 0;
	reader.size = getSize();
	loadFile();
	return &reader;
}

int getSize(){
	// from: https://www.techiedelight.com/es/find-size-of-file-c/
	struct stat st;
	stat(reader.filename, &st);
	return st.st_size;
}

void loadFile() {
	FILE *f;
	f = fopen(reader.filename, "r");

	if(f == NULL)
		exit(1);
	
	int c; //char c;
	reader.lines=(int*)malloc(sizeof(int));
	reader.lines[reader.countlines++]=0;//linea 1 inicia en el caracter 0
	reader.data = (char*) malloc((reader.size)*sizeof(char));

	if(reader.data==NULL){
		fclose(f);
		exit(1);
	}

	while ((c = fgetc(f)) != EOF) {
		if(c=='\n'){
			reader.lines[reader.countlines++]=reader.count+1;//el que le sigue a \n
			reader.lines = (int*) realloc(reader.lines, (reader.countlines+1)*sizeof(int));
		}
		reader.data[reader.count++] = c;
	}
	reader.countlines--;
	fclose(f);
}

int calcLine(){
	int i=1;
	printf("%d\n", reader.pos);
	while (reader.pos>reader.lines[i]) {
		printf("%d", i);
		printf("%s", getLine(i));
		i++;
	}
	return i-1;
}

char *getLine(int line) {
	char *codeLine="";
	if(line<= reader.countlines){
		int pos = reader.lines[line-1]; //line 2 in lines = [1,2,3]
		int sizeLine = reader.lines[line]-pos-1;
		codeLine = (char*) malloc((sizeLine)*sizeof(char));
		while (reader.data[pos]!='\n') {
			codeLine[strlen(codeLine)] = reader.data[pos++];
		}
	}
	return codeLine;
}

void show(){
	char *bar = "\033[32m|";
	int ccc=1;
	printf("%i\t",ccc++);
	for (int i = 0; i < reader.count-1 ; i++) {
		printf("%s\033[0m%c", bar, reader.data[i]);
		if(reader.data[i]=='\n'){
			printf("%i\t", ccc++);
		}
	}
	printf("\033[0m\n");
}

void avanzar(){
	reader.pos++;
}
void retroceder(){
	reader.pos--;
}
char getChar(){
	return reader.data[reader.pos];
}


