# Nome do executável
EXEC = myrb

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm # Adiciona a biblioteca matemática

# Arquivos fonte e objetos
SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regra para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(OBJS) $(EXEC) output.out teste.out

# Recompila tudo
rebuild: clean all

# Executa o programa e compara a saída
test: $(EXEC) teste.in teste.sol
	./$(EXEC) < teste.in > teste.out
	diff -u teste.sol teste.out

.PHONY: all clean rebuild test
