TARGET = main
LIBS = reader/Reader.c token/Token.c simbolos/tSimbolos.c analex/Analex.c 
MAIN = main.c
COMP = gcc

all: clean $(TARGET)

$(TARGET) : $(LIBS)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS)

clean:
	rm -f $(TARGET)

debug: clean $(TARGET)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS) -g


