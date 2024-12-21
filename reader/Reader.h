#ifndef READER_H
#define READER_H

struct Reader{
	char *filename;
	char *content;
	int size;
	int *lines;
	int countlines;
	int pos;
	int count;
};
typedef struct Reader Reader;

Reader *newReader(char *filename);
void loadFile();
void avanzar();
void irALinea(int linea);
char getCC();
int calcLinea();
int getSize();
void mostrar();
#endif /* ifndef READER_H */
