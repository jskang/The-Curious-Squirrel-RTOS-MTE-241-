#ifndef _MEMORY_MAP_
#define _MEMORY_MAP_

/* Include Libraries */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

/* Define constants*/
#define BUFFERSIZE 1024
#define MAXCHAR 512

/* Define structures */
typedef struct{
	int ok_flag;
	char indata[MAXCHAR];
	int length;
} iobuf;

iobuf *in_mem_p_kbd;
iobuf *out_mem_p_crt;

void crt_i_process();
void kbd_i_process();

#endif
