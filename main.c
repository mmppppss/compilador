#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

char *vector;
int count = 0;
int *lines;
int countlines=0;
int pos=0;
/**
 * guarda los Caracteres en un vector de 
 * caracteres de tamaño 
 *  fileSize*sizeOf(char)
 *  un caracter pesa 8 bits o 1 byte
 *  Ex: archivo de 3 bytes 
 *  	3*sizeOf(char) = 24 bits
 *    
 *
 * lineas  1 2 3 4 5 ...			
 * lines =[0,n,x,y,z,...]
 * guarda el caracter de inicio de x linea 
 * en lines[x-1] 
 * 
 */
char *load_file(char *filename) {
	FILE *f;
	f = fopen(filename, "r");

    if (f == NULL) {
		exit(1);
    }
	// from: https://www.techiedelight.com/es/find-size-of-file-c/
    struct stat st;
    stat(filename, &st);
    off_t size = st.st_size;

	char c;
	int capacidad = size;
	char *vector = NULL;
	lines=(int*)malloc(sizeof(int));
	lines[countlines++]=0;//linea 1 inicia en el caracter 0
    vector = (char *)malloc((capacidad + 1)* sizeof(char));// reserva capacidad*sizeof(char) 8 en memoria
	if(vector==NULL){
		fclose(f);
		exit(1);
	}
    while ((c = fgetc(f)) != EOF) {
		if(c=='\n'){
			lines[countlines++]=count+1;//el que le sigue a \n
			lines = (int*) realloc(lines, (countlines+1)*sizeof(int));
		}
		vector[count++] = c;
    }
	countlines--;
	vector[count]='\0';
	fclose(f);
	return vector;
};
void show_vector(char *vector) {
	char *bar = "\033[32m|";
	int ccc=1;
	printf("%i\t",ccc++);
	for (int i = 0; i < count ; i++) {
		printf("%s\033[0m%c", bar,vector[i]);
		if(vector[i]=='\n'){
			printf("%i\t", ccc++);
		}
	}
	printf("\033[0m\n");
}

void show_line(char *vector, int line){
	if(line<=countlines){
		int pos = lines[line-1]; //line 2 in lines = [1,2,3]
		while (vector[pos]!='\n') {
			printf("%c", vector[pos++]);
		}
		printf("\n");
	}
}
void avanzar(){
	pos++;
}
char getCC(){
	return vector[pos];
}
void analex(){
	char* ac="";
	int peso, estado;
	
	for(;;){
		char c = getCC();
		switch(estado){
			case 0:
				if(c==' ')
					avanzar();
				else if(isdigit(c)!=0){
					ac+=c;
					estado=1;
					avanzar();
				}
		}
	}
}
int main(int argc, char *argv[])
{
	char *filename = argv[1];
	vector = load_file(filename);
	printf("Caracteres: %d\n", count);
	printf("Lineas: %i\n", countlines);
	
	for (int i = 2; i < argc; i++) {
		char *opt= "-s";
		char *opt2= "-v";
		if(strcmp(argv[i],opt)==0){
			int *ln;
			printf("Mostrar linea x: ");
			scanf("%i", ln);
			show_line(vector, *ln);
		}
		if(strcmp(argv[i],opt2)==0){
			show_vector(vector);
		}
	}
	free(vector);
	return 0;
}
