CC = gcc
CFLAGS= -c
LINK = gcc
LNFLAGS = -g
FLAGS="-Wall" "-I"
OBJS = init.o iproc.o primitves.o queues.o

all: init keyboard crt

#make executables
init: $(OBJS) 
	$(LINK) -o run $(OBJS)

keyboard: keyboard.o
	$(LINK)  -o $@ keyboard.o -lrt

crt: crt.o
	$(LINK) -o $@ crt.o -lrt

#compilation

init.o: init.c iproc.c rtx.h kbcrt.h
	$(CC) $(CFLAGS) init.c

keyboard.o: keyboard.c kbcrt.h
	$(CC) $(CFLAGS) keyboard.c

crt.o: crt.c kbcrt.h
	$(CC) $(CFLAGS) crt.c

iproc.o: iproc.c atomic.c 
	$(CC) $(CFLAGS) iproc.c

primitives.o: primitives.c queues.c rtx.h
	$(CC) $(CFLAGS) primitives.c

queues.o: queues.c
	$(CC) $(CFLAGS) queues.c

#clean
clean:
	rm *.o init keyboard crt

