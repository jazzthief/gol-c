CC = gcc
CFLAGS = -I.
DEPS = gol.h
ODIR = obj

_OBJ = gol.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core

$(ODIR)/%.o: %.c $(DEPS)
	@ mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

gol: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
