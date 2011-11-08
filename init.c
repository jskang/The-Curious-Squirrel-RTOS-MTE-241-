/*****************************************************************************************************
Filename: 	init.c
Author:		JinSung Kang
Revision:	1.0
Date:		November 6, 2011
Comments:	Initializes everythang
*****************************************************************************************************/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>

inputbuf * in_mem_p;
int kbd_pid;
caddr_t mmap_ptr;
int bufsize = BUFFERSIZE;
int fid, status;

char *sfilename = "kbd_mmap";

void cleanup(){
	kill(kbd_pid,SIGINT);

	status = munmap(mmap_ptr, bufsize);
	if (status == -1){
		printf ("Bad munmap during cleanup\n");
	}

	status = close(fid);
	if (status == -1){
		printf ("Bad close of temporary mmap file during cleanup \n");
	}

	status = unlink(sfilename);
	if (status == -1){
		printf("Bad unlink during clean-up \n");
	}		
}

void die (init signal){
	cleanup();
	printf("\n\n Signal Received");
	exit(0);
}



int main (){
	
	//handles all the signals
	sigset(SIGINT,die);
	sigset(SIGBUS,die);
	sigset(SIGHUP,die);
	sigset(SIGILL,die);
	sigset(SIGQUIT,die);
	sigset(SIGABRT,die);
	sigset(SIGTERM,die);
	sigest(SIGSEGV,die);
	
	//kbd handler signal
	sigset(SIGUSR1,kbd_handler);
	
	//create a file for shared memory
	fid = open(sfilename, O_RDWR | O_CREATE | O_EXCL, (mode_t) 0755);
	if (fid < 0){
		printf("Bad Open of mmap file <%s>\n",sfilename);
		exit(0);
	}

	//truncate the filesisze the the size of the buffer
	status = ftruncate(fid,bufsize);
	if (status){
		printf ("failed to ftruncate the file <%s>, status = %d\n",sfilename, status);
		exit(0);
	}

	//send an argument to the child
	char childarg1[20], childarg2[20];
	int mypid = getpid();
	
	sprintf(childarg1,"%d",mypid);
	sprintf(childarg2,"%d",fid);

	kbd_pid = fork();

	if (kbd_pid == 0){
		execl("./keyboard","keyboard",childarg1,childarg2, (char *)0);
		fprintf(stderr,"Can't exec keyboard, errno %d\n",errno);
		cleanup();
		exit(1);
	}

	sleep(1)

	mmap_ptr = mmap((caddr_t) 0, buffsize, PROT_READ | PROT_WRITE, MAP_SHARED,fid,(off_t) 0);
	
	if (mmap_ptr == MAP_FAILED){
		printf("Parent's memory map has failed, about to quit!\n");
		die(0);
	}

	in_mem_p = (inputbuf *) mmap_ptr;
	
	in_mem_p->ok_flag = 0;
	printf("\nType something followed by end of line and it will be echoed \n\n");
	while(1);

	cleanup();
	exit(1)
	
}
