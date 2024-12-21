#ifndef READER_H
#define READER_H

struct Reader{
	char *filename;
	char *content;
	int *lines;
	int countlines;
	int pos;
	int count;
	int size;
};
typedef struct Reader Reader;

Reader *newReader(char *filename);
void loadFile();
void avanzar();
void irALinea(int linea);
void mostrar();
void mostrarCodigo();
void getLinea(int linea);
char getCC();
int calcLinea();
int getSize();
char* concat(char* s, char c);
#endif /* ifndef READER_H */
