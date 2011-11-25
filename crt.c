/*
 * keyboard.c
 *
 * CRT Display - emulate a hardware interrupt
 * display and signal the parent process when displayed
 *
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#include "kbcrt.h"

int bufsize = BUFFERSIZE;

void crt_die(int signal){
	exit(0);
}

int main (int argc, char * argv[]){
	int parent_pid, fid;
	caddr_t mmap_ptr;
	iobuf *in_mem_p;

	sigset(SIGINT,crt_die);

	sscanf(argv[1], "%d", &parent_pid );
	sscanf(argv[2], "%d", &fid );

	mmap_ptr = mmap((caddr_t) 0, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, fid, (off_t) 0);

	if (mmap_ptr == MAP_FAILED){
		printf("Child memory map has failed, CRT is aborting!\n");
		crt_die(0);
	}

	in_mem_p = (iobuf*) mmap_ptr; // now we have a shared memory pointer to the CRT shared memory
	in_mem_p->ok_flag = 0;
	

	do{
	    	if(in_mem_p->ok_flag == 1) { //if there is something to display, i.e. content in outdata[]
            		printf("\nOutput: %s\n\n", in_mem_p->indata);
			fflush(stdout);
                	strcpy(in_mem_p->indata,"");
			in_mem_p->length = 0;
			in_mem_p->ok_flag = 0;
			kill(parent_pid, SIGUSR2);
        	}
	}while(1);
}
