TARGET = main
LIBS = libs/reader.c libs/Token.c libs/lTokens.c libs/tSimbolos.c
MAIN = main.c
COMP = gcc
FILETEST = cuadrado.c
all: clean $(TARGET)

$(TARGET) : $(LIBS)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS)

clean:
	rm -f $(TARGET)

# Regla para ejecutar el programa
run: clean $(TARGET)
	./$(TARGET) $(FILETEST) prueba.x -v -t

.PHONY: all clean run
