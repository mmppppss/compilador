TARGET = main
LIBS = reader/Reader.c token/Token.c simbolos/tSimbolos.c analex/Analex.c parser/Parser.c
MAIN = main.c
COMP = gcc
FLAGS = -lm
all: clean $(TARGET)

$(TARGET) : $(LIBS)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS) $(FLAGS)

clean:
	rm -f $(TARGET)

debug: clean $(TARGET)
	$(COMP) -o $(TARGET) $(MAIN) $(LIBS) -g


