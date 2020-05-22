CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -D_GNU_SOURCE -g
RM=rm -fv
.PHONY: all clean
all: client.out server.out

infos.o: infos.c infos.h
	$(CC) $(CFLAGS) -c -o $@ $<
client.out: client.c  infos.o
	$(CC) $(CFLAGS) -o $@ $^
serveur.out: serveur.c infos.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	$(RM) *.o *.out
