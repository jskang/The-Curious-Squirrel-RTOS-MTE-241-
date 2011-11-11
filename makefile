CC = gcc
CFLAGS= -c -g
LINK = gcc
LNFLAGS = -g

all: init keyboard crt

#make executables
init: init.o
	$(LINK) init.o iproc.o

keyboard: keyboard.o
	$(LINK) $(LNFLAGS) -o $@ keyboard.o -lrt

crt: crt.o
	$(LINK) $(LNFLAGS) -o $@ crt.o -lrt

#compilation

init.o: init.c
	$(CC) $(CFLAGS) init.c

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) keyboard.c

crt.o: crt.c 
	$(CC) $(CFLAGS) crt.c

iproc.o: iproc.c
	$(CC) $(CFLAGS) iproc.c

#clean
clean:
	rm *.o init keyboard crt
