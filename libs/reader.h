#ifndef READER_H
#define READER_H

typedef struct{
	char *data;
	char *filename;
	int *lines;
	int countlines;
	int pos;
	int count;
	int size;
}Reader;

extern Reader reader;

Reader *createReader(char *filename);

char* concat(char* s, char c);
int getSize();
void loadFile();
int calcLine();
char *getLine(int line);
void showCode();
void avanzar();
void irAlinea(int line);
void retroceder();
char getChar();
#endif /* ifndef Reader */
