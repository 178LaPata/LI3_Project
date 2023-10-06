all: programa-principal 

IDIR = $/Includes

CC = gcc
CFLAGS = -Wall -I$(IDIR) -g `pkg-config --cflags glib-2.0` -c
LDFLAGS = `pkg-config --libs glib-2.0` -lm

SDIR = Code/SRC
ODIR = Code/SRC/obj

_OBJ = users.o flights.o reservations.o valid.o date.o catalog.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
    mkdir -p $(@D)
    mkdir -p Resultados
    $(CC) $(CFLAGS) -o $@ $<


programa-principal: $(OBJ) $(ODIR)/programa_principal.o
    $(CC) $^ $(LDFLAGS) -o $@
    

.PHONY: clean

clean:
    rm -r $(ODIR)
    rm -r Resultados
    rm programa-principal
