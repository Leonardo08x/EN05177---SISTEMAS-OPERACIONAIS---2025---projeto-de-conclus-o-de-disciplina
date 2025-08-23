# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/programa

# Lista de arquivos .c e .o
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# -----------------------
# Regras principais
# -----------------------
all: $(TARGET)

# Compila o executável a partir dos objetos
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada arquivo .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria pastas se não existirem
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
