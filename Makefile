# --- Configuração do Compilador e Flags ---
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
IDIR = -Iinclude
LDFLAGS = -lpthread

# --- Configuração dos Arquivos ---
# Detecta o Sistema Operacional
ifeq ($(OS), Windows_NT)
    TARGET = forca.exe
    RM = del
else
    TARGET = forca
    RM = rm -f
endif

# Encontra todos os arquivos .c dentro da pasta src
SOURCES = $(wildcard src/*.c)

# Regra padrão: executada quando você digita apenas "make"
all: $(TARGET)

# Regra para compilar o programa
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(IDIR) $^ -o $@ $(LDFLAGS)
	@echo "Projeto compilado com sucesso: $(TARGET)"

# Regra para compilar E executar o projeto
run: all
	...

# Regra para limpar os arquivos compilados
clean:
	...

# Declara regras que não geram arquivos
.PHONY: all run clean