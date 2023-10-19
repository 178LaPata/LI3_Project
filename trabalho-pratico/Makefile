
IDIR = $/includes/model

CC = gcc
CFLAGS = -Wall -I$(IDIR) -g `pkg-config --cflags glib-2.0` -c
LDFLAGS = `pkg-config --libs glib-2.0` -lm

SDIR = src/model
ODIR = src/model/obj

_OBJ = users.o flights.o reservations.o passengers.o valid.o date.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(@D)
	mkdir -p Resultados
	$(CC) $(CFLAGS) -o $@ $<


main: $(OBJ) $(ODIR)/main.o
	$(CC) $^ $(LDFLAGS) -o $@


.PHONY: clean

clean:
	rm -r $(ODIR)
	rm -r Resultados
	rm main
