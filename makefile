CC = gcc
CFLAGS= -c
LINK = gcc
LNFLAGS = -g

OBJS = init.o iproc.o primitives.o queues.o atomic.o

all: init keyboard crt

#make executables
init: $(OBJS) 
	$(LINK) -o rtx $(OBJS)

keyboard: keyboard.o
	$(LINK)  -o $@ keyboard.o -lrt

crt: crt.o
	$(LINK) -o $@ crt.o -lrt

#compilation

init.o: init.c 
	$(CC) $(CFLAGS) init.c

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) keyboard.c

crt.o: crt.c 
	$(CC) $(CFLAGS) crt.c

iproc.o: iproc.c 
	$(CC) $(CFLAGS) iproc.c

primitives.o: primitives.c
	$(CC) $(CFLAGS) primitives.c

queues.o: queues.c
	$(CC) $(CFLAGS) queues.c

atomic.o: atomic.c
	$(CC) $(CFLAGS) atomic.c

#clean
clean:
	rm *.o rtx keyboard crt *_mmap

