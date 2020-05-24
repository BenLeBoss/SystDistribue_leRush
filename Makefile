CC=gcc
CFLAGS= -g
RM=rm -fv
.PHONY: all clean
all: client.out serveur.out
infos.o: infos.c infos.h
	$(CC) $(CFLAGS) -c -o $@ $<
client.out: client.c infos.o
	$(CC) $(CFLAGS) -o $@ $^
serveur.out: serveur.c infos.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	$(RM) *.o *.out
