# Constantes
SRC     = main.c ints.c sieve.c
OBJ     = main.o ints.o sieve.o
HEADER  = sieve.h ints.h
FLAGS   = -lpthread
EXEC    = trab1

# Compila e gera executável de uma vez
all: obj exe

# Gera arquivos objeto .o
obj: $(SRC)
	gcc -c $(SRC)

# Gera arquivo executável
exe: $(OBJ)
	gcc $(OBJ) $(FLAGS) -o $(EXEC)

# Executa programa sem passagem de parâmetro
run: $(EXEC)
	./$(EXEC)

# Remove arquivos gerados
clean: $(OBJ) $(EXEC)
	rm $(OBJ) $(EXEC)
