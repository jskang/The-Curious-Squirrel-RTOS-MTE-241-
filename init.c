/************************************************************************************************
Filename: 	init.c
Author:		JinSung Kang
Revision:	1.0
Date:		November 6, 2011
Comments:	Initializes everythang
**********************************************************************************************/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#include "rtx.h"
#include "kbcrt.h"
#include "iproc.h"

int kbd_pid, crt_pid;
caddr_t kbd_mmap, crt_mmap;
int bufsize = BUFFERSIZE;
int kbd_fid, crt_fid, kbd_status , crt_status;

char *sfilename_kbd = "kbd_mmap";
char *sfilename_crt = "crt_mmap";

void cleanup(){
	kill(kbd_pid,SIGINT);
	kill(crt_pid,SIGINT);
	
	//removes memory mapping	
	kbd_status = munmap(kbd_mmap, bufsize);
	crt_status = munmap(crt_mmap, bufsize);

	if (kbd_status == -1){
		printf ("Bad munmap during cleanup\n");
	}
	
	if (crt_status == -1){
		printf ("Bad munmap during cleanup\n");
	}

	//close the temporary mmap files
	kbd_status = close(kbd_fid);
	crt_status = close(crt_fid);

	if (kbd_status == -1){
		printf ("Bad close of temporary mmap file during cleanup \n");
	}
	
	if (crt_status == -1){
		printf ("Bad close of temporary mmap file during cleanup \n");
	}

	//delete the temporary mmap files
	kbd_status = unlink(sfilename_kbd);
	crt_status = unlink(sfilename_crt);

	if (kbd_status == -1){
		printf("Bad unlink during clean-up \n");
	}		

	if (crt_status == -1){
		printf("Bad unlink during clean-up \n");
	}
}

void die (int signal){
	cleanup();
	printf("Signal %i",signal);
	printf("\n\n Signal Received\n");
	exit(0);
}

int initialize_table(){
	initialization_table i_table[N_TOTAL_PCB];	
        // Process P only required for partial implementation.
        i_table[0].pid = PID_PROCESS_P;
        i_table[0].state = NO_BLK_RCV;
        i_table[0].priority = 0;

        i_table[1].pid = PID_I_PROCESS_CRT;
        i_table[1].state = I_PROCESS;
        i_table[1].priority = 0;

        i_table[2].pid = PID_I_PROCESS_KBD;
        i_table[2].state = I_PROCESS;
        i_table[2].priority = 0;

        i_table[3].pid = PID_I_PROCESS_TIMER;
        i_table[3].state = I_PROCESS;
        i_table[3].priority = 0;
	
	int i;
       
        for(i = 0;i<TEMP_NUM_PROCESS;i++){
                pcbList[i] = (pcb*)(malloc(sizeof(pcb)));
                pcbList[i]->inbox = (msg_queue*)(malloc(sizeof(msg_queue)));
                if(pcbList[i] == NULL){
                        return INVALID_QUEUE_ERROR;
                }
                pcbList[i]->pid = i_table[i].pid;
                pcbList[i]->state = i_table[i].state;
                pcbList[i]->priority = i_table[i].priority;
                pcbList[i]->next = NULL;
                pcbList[i]->inbox->head = NULL;
                pcbList[i]->inbox->tail = NULL;
        }
	
	Msg_Env* tempMsgEnv;
	tempMsgEnv = (Msg_Env*) malloc (sizeof(Msg_Env));
	msg_enqueue(pcbList[PID_PROCESS_P]->inbox,tempMsgEnv);

	current_process = pcbList[0];
	return 1;
}


void initialize_data_structures (){
	int i;
	for (i = 0; i < 4; i++){
		priority_ready_queue[i] = (pcb_queue*)(malloc(sizeof(pcb_queue)));
	}

	blocked_message_envelope = (pcb_queue*) (malloc(sizeof(pcb_queue)));
	blocked_message_receive = (pcb_queue*)(malloc(sizeof(pcb_queue)));
	sleep_queue = (pcb_queue*)(malloc(sizeof(pcb_queue)));

	all_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));
	free_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));
	all_i_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));
	free_i_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));
}

void init (){
	initialize_data_structures();
	initialize_table();
	//handles all the signals
	sigset(SIGINT,die);
	sigset(SIGBUS,die);
	sigset(SIGHUP,die);
	sigset(SIGILL,die);
	sigset(SIGQUIT,die);
	sigset(SIGABRT,die);
	sigset(SIGTERM,die);
	sigset(SIGSEGV,die);
	
	//kbd handler signal
	sigset(SIGUSR1,kbd_i_process);
	sigset(SIGUSR2,crt_i_process);
	
	//create a file for shared memory
	kbd_fid = open(sfilename_kbd, O_RDWR | O_CREAT | O_EXCL, (mode_t) 0755);
	crt_fid = open(sfilename_crt, O_RDWR | O_CREAT | O_EXCL, (mode_t) 0755);

	if (kbd_fid < 0){
		printf("Bad Open of mmap file <%s>\n",sfilename_kbd);
		exit(0);
	}
	
	if (crt_fid < 0){
		printf("Bad Open of mmap file <%s>\n",sfilename_crt);
		exit(0);
	}
	

	//truncate the filesisze the the size of the buffer
	kbd_status = ftruncate(kbd_fid,bufsize);
	crt_status = ftruncate(crt_fid,bufsize);

	if (kbd_status){
		printf ("failed to ftruncate the file <%s>, status = %d\n",sfilename_kbd, kbd_status);
		exit(0);
	}

	if (crt_status){
		printf ("failed to ftruncate the file <%s>, status = %d\n",sfilename_crt, crt_status);
		exit(0);
	}
	
	kbd_mmap = mmap((caddr_t) 0, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED,kbd_fid,(off_t) 0);
        crt_mmap = mmap((caddr_t) 0, bufsize, PROT_READ | PROT_WRITE, MAP_SHARED,crt_fid,(off_t) 0);

        
        if (kbd_mmap == MAP_FAILED){
                printf("Parent's memory map has failed, about to quit!\n");
                die(0);
        }
        
        if (crt_mmap == MAP_FAILED){
                printf("Parent's memory map has failed, about to quit!\n");
                die(0);
        }
        
        in_mem_p_kbd = (iobuf *) kbd_mmap;
        out_mem_p_crt = (iobuf *) crt_mmap;

        in_mem_p_kbd->ok_flag = 0;
        out_mem_p_crt->ok_flag = 0;

	//send an argument to the child
	char childarg1_kbd[20], childarg2_kbd[20];
	char childarg1_crt[20], childarg2_crt[20];

	int mypid = getpid();
	
	sprintf(childarg1_kbd,"%d",mypid);
	sprintf(childarg2_kbd,"%d",kbd_fid);

	sprintf(childarg1_crt,"%d",mypid);
	sprintf(childarg2_crt,"%d",crt_fid);

	kbd_pid = fork();

	if (kbd_pid == 0){
		execl("./keyboard","keyboard",childarg1_kbd,childarg2_kbd, (char *)0);
		fprintf(stderr,"Can't exec keyboard, errno %d\n",errno);
		cleanup();
		exit(1);
	}
	
	else{		
		sleep(1);
		crt_pid = fork();

		if (crt_pid == 0){
			execl("./crt","crt",childarg1_crt, childarg2_kbd, (char *)0);
			fprintf(stderr, "Can't exec crt, errno %d\n",errno);
			cleanup();
			exit(1);
		}
	}	
	sleep(1);

	printf("\nType something followed by end of line and it will be echoed \n\n");
}
