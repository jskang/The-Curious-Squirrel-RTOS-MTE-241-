CC = gcc
CFLAGS= -c -g -Wall
LINK = gcc
LNFLAGS = -g

OBJS = init.o iproc.o primitives.o queues.o atomic.o kernel.o userProcesses.o userAPI.o

all: init keyboard crt

#make executables
init: $(OBJS) 
	$(LINK) -o iRTX-G17 $(OBJS)

keyboard: keyboard.o
	$(LINK)  -o $@ keyboard.o -lrt

crt: crt.o
	$(LINK) -o $@ crt.o -lrt

#compilation

compile : $(OBJS)

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

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c

userProcesses.o: userProcesses.c
	$(CC) $(CFLAGS) userProcesses.c

userAPI.o: userAPI.c
	$(CC) $(CFLAGS) userAPI.c


#clean
clean:
	rm *.o iRTX-G17 keyboard crt *_mmap

