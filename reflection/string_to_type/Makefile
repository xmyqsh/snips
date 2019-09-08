CC=g++
CFLAGS=-I.
DEPS = Metadata.h Test.h
OBJ = main.o Test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
