all: programa-principal programa-testes

IDIR = includes
CC = gcc
CFLAGS = -Wall -I$(IDIR) -g -O -O2 `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0` -lm

SDIR = src
ODIR = obj

SOURCES = $(wildcard $(SDIR)/*.c)
SOURCES_NO_MAIN = $(filter-out $(SDIR)/programa-principal.c $(SDIR)/programa-testes.c, $(SOURCES))

_OBJ = $(SOURCES_NO_MAIN:$(SDIR)/%.c=%.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	mkdir -p Resultados
	mkdir -p entrada
	$(CC) $(CFLAGS) -c $< -o $@

programa-principal: $(OBJ) $(ODIR)/programa-principal.o
	$(CC) $^ $(LDFLAGS) -o $@

programa-testes: $(OBJ) $(ODIR)/programa-testes.o
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean

clean:
	rm -f programa-principal
	rm -f programa-testes
	rm -r $(ODIR)
	rm -r Resultados
	rm -r entrada