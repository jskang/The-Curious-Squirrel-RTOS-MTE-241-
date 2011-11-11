/*
 * keyboard.c
 *
 * CRT Display - emulate a hardware interrupt
 * display and signal the parent process when displayed
 *
 *
 */
#include "rtx.h"

#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int bufsize = BUFFERSIZE;
int buf_index = 0;

void crt_die(int signal)
{
  exit(0);
}

int main (int argc, char *crt[])
{
	int parent_pid, fid;
	caddr_t mmap_ptr;
	char c;

	sigset(SIGINT,crt_die);

	sscanf(crt[1], "%d", &parent_pid );
	sscanf(crt[2], "%d", &fid );

	crt_mmap_ptr = mmap((caddr_t) 0, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED, fid, (off_t) 0);

    if (crt_mmap_ptr == MAP_FAILED)
    {
        printf("Child memory map has failed, CRT is aborting!\n");
	    crt_die(0);
    }

	outputbuf *in_Cmem;  // in CRT memory (shared)
	in_Cmem = (inputbuf*) mmap_ptr; // now we have a shared memory pointer to the CRT shared memory

	in_Cmem->ready_flag = 0;

	while(1)
	{
	    if(in_Cmem->outdata[buf_index] != NULL)  //if there is something to display, i.e. content in outdata[]
	    {
                printf("%s", in_Cmem->outdata[buf_index])
                buf_index++;
            }
            else if(in_Cmem->outdata[buf_index] == NULL && buf_index > 0)  // for debugging, this will show the finish '!'
            {
                printf("!"); //this is stupid for but it shows when the outdata limit has been reached
            }
            else
            {
                printf("nothing to display");
                in_Cmem->ready_flag=1;           // set ready status bit, ??
                kill(parent_pid, SIGUSR2);    // send a signal to parent
                buff_index = 0;               // reset count of buf_index
		while(in_Cmem->ready_flag = 1) // checks to see if CRT is ready
                {
                   usleep(100000);
                }
            }
	}

}
