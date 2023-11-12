
IDIR = $/includes

CC = gcc
CFLAGS = -Wall -I$(IDIR) -g `pkg-config --cflags glib-2.0` -c
LDFLAGS = `pkg-config --libs glib-2.0` -lm

SDIR = src/
ODIR = src/model/obj

_OBJ = users.o flights.o reservations.o passengers.o valid.o catalog.o date.o output.o programa-principal.o queries.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	mkdir -p Resultados
	$(CC) $(CFLAGS) -o $@ $<


programa-principal: $(OBJ) $(ODIR)/programa-principal.o
	$(CC) $^ $(LDFLAGS) -o $@


.PHONY: clean

clean:
	rm -r $(ODIR)
	rm -r Resultados
	rm programa-principal
