#include "reader/Reader.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Reader reader;
	reader = *newReader(argv[1]);
	loadFile();
	mostrar();
	return 0;
}
