# Nome do executável
EXEC = myrb

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Arquivos fonte e objetos
SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)

# Regra padrão (compilar o programa)
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos .c em .o
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
    rm -f $(OBJS) $(EXEC)

# Regra para recompilar do zero
rebuild: clean all