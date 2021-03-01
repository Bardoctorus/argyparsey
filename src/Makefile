IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -W -O

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = program.o util.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ && rm -f program