/*
 * keyboard.c
 *
 * CRT Display - emulate a hardware interrupt
 * display and signal the parent process when displayed
 *
 *
 */

#include <signal.h>
#include "kbcrt.h"
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int bufsize = BUFFERSIZE;

void crt_die(int signal){
  exit(0);
}

int main (int argc, char *crt[]){

	int parent_pid, fid;
	caddr_t crt_mmap_ptr;


	sigset(SIGINT,crt_die);

	sscanf(crt[1], "%d", &parent_pid );
	sscanf(crt[2], "%d", &fid );

	crt_mmap_ptr = mmap((caddr_t) 0, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, fid, (off_t) 0);

	if (crt_mmap_ptr == MAP_FAILED){
		printf("Child memory map has failed, CRT is aborting!\n");
		crt_die(0);
	}

	iobuf *in_Cmem;  // in CRT memory (shared)
	in_Cmem = (iobuf*) crt_mmap_ptr; // now we have a shared memory pointer to the CRT shared memory

	in_Cmem->ok_flag = 0;

	while(1){
	    	if(in_Cmem->ok_flag) { //if there is something to display, i.e. content in outdata[]
            		printf("%s", in_Cmem->indata);
                	strcpy(in_Cmem->indata,"");
                //reset everything in the memory buffer
        	}

        	else{
                	kill(parent_pid, SIGUSR2);    // send a signal to parent
                	usleep(10000);
        	}
	}

}
