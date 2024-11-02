TARGET = main
LIBS = libs/reader.c libs/Token.c
MAIN = main.c
COMP = gcc
FILETEST = cuadrado.c
all: $(TARGET)

$(TARGET) : $(LIBS)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS)

clean:
	rm -f $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET) $(FILETEST) -t -v -s

.PHONY: all clean run
