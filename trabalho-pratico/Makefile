IDIR = includes
CC = gcc
CFLAGS = -Wall -I$(IDIR) -g -O2 `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0` -lm

SDIR = src
ODIR = obj

# Adicione aqui os subdiretórios do seu projeto
SUBDIRS = controller model view

# Utilize a função wildcard para encontrar todos os arquivos .c
SOURCES = $(wildcard $(SDIR)/*.c $(SDIR)/controller/*.c $(SDIR)/model/*.c $(SDIR)/view/*.c)

# Substitua os caminhos dos arquivos fonte pelos caminhos dos arquivos objeto
_OBJ = $(SOURCES:$(SDIR)/%.c=%.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Regra para criar os diretórios de objetos
$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	mkdir -p Resultados
	mkdir -p Entradas
	$(CC) $(CFLAGS) -c $< -o $@
	
# Regra para compilar o programa principal
programa-principal: $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# Marca 'clean' como uma operação que não está associada a arquivos
.PHONY: clean

clean:
	rm -f programa-principal
	rm -r $(ODIR)
	rm -r Resultados
	rm -r Entradas