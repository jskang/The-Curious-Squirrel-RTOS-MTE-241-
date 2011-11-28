#ifndef _MEMORY_MAP_
#define _MEMORY_MAP_
#include <signal.h>
/* Include Libraries */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>

/* Define constants*/
#define BUFFERSIZE 5000
#define MAXCHAR 2450 

/* Define structures */
typedef struct{
	int ok_flag;
	char indata[MAXCHAR];
	int length;
} iobuf;

#endif
