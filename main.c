#include "reader/Reader.h"
#include "analex/Analex.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Reader *reader;
	reader = newReader(argv[1]);
	mostrar();
	mostrarCodigo();
	mostrarTokens(reader);
	return 0;
}
