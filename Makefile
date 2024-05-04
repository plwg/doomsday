# Compiler to use
CC=gcc

# Compiler flags
CFLAGS=-O3 -Wall

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o 