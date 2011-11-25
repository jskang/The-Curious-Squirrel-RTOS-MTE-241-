/***********************************************************************************************
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
#include "queues.h"
#include "userProcesses.h"
#include "testing_functions.h"

int kbd_pid, crt_pid;
caddr_t kbd_mmap, crt_mmap;
int bufsize = BUFFERSIZE;
int kbd_fid, crt_fid, kbd_status , crt_status;
jmp_buf kernel_buf;
initialization_table i_table[N_TOTAL_PCB];

char *sfilename_kbd = "kbd_mmap";
char *sfilename_crt = "crt_mmap";


//Used to cleanup all the processes and memory maps after the kill function
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

//called by the sigset signal handler
void die (int signal){
	cleanup();
	printf("\n\nSignal %i received. Terminating Program.\n\n",signal);
	exit(0);
}

int initialize_table(){

        // Process P only required for partial implementation.

        i_table[0].pid = PID_I_PROCESS_CRT;
        i_table[0].state = I_PROCESS;
        i_table[0].priority = 0;
	i_table[0].stack_address=(void *) kbd_i_process;

        i_table[1].pid = PID_I_PROCESS_KBD;
        i_table[1].state = I_PROCESS;
        i_table[1].priority = 0;
	i_table[1].stack_address =(void *) crt_i_process;

        i_table[2].pid = PID_I_PROCESS_TIMER;
        i_table[2].state = I_PROCESS;
        i_table[2].priority = 0;
	i_table[2].stack_address =(void *) timer_i_process;

	i_table[3].pid = PID_PROCESS_A;
	i_table[3].state = READY;
	i_table[3].priority = 0;
	i_table[3].stack_address =(void *) process_a;
	
	i_table[4].pid = PID_PROCESS_B;
	i_table[4].state = READY;
	i_table[4].priority = 0;
	i_table[4].stack_address =(void *) process_b;

	i_table[5].pid = PID_PROCESS_C;
	i_table[5].state = READY;
	i_table[5].priority = 0;
	i_table[5].stack_address =(void *) process_c;
	
	i_table[6].pid = PID_PROCESS_CCI;
	i_table[6].state = READY;
	i_table[6].priority = 0;
	i_table[6].stack_address =(void *) process_cci;

	i_table[7].pid = PID_PROCESS_CLOCK;
	i_table[7].state = READY;
	i_table[7].priority = 0;
	i_table[7].stack_address =(void *) process_clock;
	
	i_table[8].pid = PID_PROCESS_NULL;
	i_table[8].state = READY;
	i_table[8].priority = 3;
	i_table[8].stack_address =(void *) process_null;
	return 1;
}

int init_pcb(){
	int i;
       
        for(i = 0;i<N_TOTAL_PCB;i++){
                
		pcbList[i] = (pcb*)(malloc(sizeof(pcb))); //creates pcbs
		initialize_pcb(pcbList[i]);
		if(pcbList[i] == NULL){
                        return INVALID_QUEUE_ERROR;
                }

		
                pcbList[i]->pid = i_table[i].pid;
                pcbList[i]->state = i_table[i].state;
                pcbList[i]->priority = i_table[i].priority;
		pcbList[i]->stack =(char*)(malloc(STACKSIZE)) + STACKSIZE - STACK_OFFSET;
		pcbList[i]->process_code = i_table[i].stack_address;
		
		if ((i > 2 && i <6)|| i==8){
			rpq_enqueue(pcbList[i]);
		}
		else{
			enqueue(i_process_queue,pcbList[i]);
		}
		init_context_save(pcbList[i]);
	}
	current_process = pcbList[3];
	return 1;
}

void init_context_save (pcb *tmp_pcb){
	char* temp_sp = NULL;
	pcb* temp = tmp_pcb;
	if (setjmp(kernel_buf)==0){
		temp_sp = (void *) temp->stack;
		__asm__("movl %0,%%esp" :"=m" (temp_sp));
		if (setjmp(temp->jbdata)==0){
			longjmp(kernel_buf,1);
		}
		else{
			void (*tmp) ();
			tmp = (void*) current_process->process_code;
			tmp();
			printf("we have a problem\n");
		}
	}
}

int init_msg_env (){
	int i, debug;	
	Msg_Env* tempMsg;
	//initialize envelopes for user processes
	for(i = 0;i < 1; i++){//N_MSG_ENV
		tempMsg = (Msg_Env*)malloc(sizeof(Msg_Env));
		if(tempMsg == NULL){
			return INVALID_MSG_POINTER;
		}
		msg_enqueue_all(tempMsg);
		msg_enqueue(free_envelopes,tempMsg);
	}
return 1;
}



void initialize_data_structures (){

	initialize_rpq_queue();

	i_process_queue = (pcb_queue*)(malloc(sizeof(pcb_queue)));	
	blocked_message_envelope = (pcb_queue*) (malloc(sizeof(pcb_queue)));
	blocked_message_receive = (pcb_queue*)(malloc(sizeof(pcb_queue)));
	sleep_queue = (pcb_queue*)(malloc(sizeof(pcb_queue)));

	all_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));
	free_envelopes = (msg_queue*)(malloc(sizeof(msg_queue)));

	initialize_queue(i_process_queue);
	initialize_queue(blocked_message_envelope);
	initialize_queue(blocked_message_receive);

	initialize_msg_queue(all_envelopes);
	initialize_msg_queue(free_envelopes);

	//initializing the trace buffer
	message_buffer= (msg_trace_buffer*)malloc(sizeof(msg_trace_buffer));
	initialize_msg_trace(message_buffer);

}

void init (){
	int i;
	//initializes all the data structures
	initialize_data_structures();
	initialize_table();
	init_pcb();
	i = init_msg_env();


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
	sigset(SIGALRM,timer_i_process);

	ualarm(100000, 100000);	
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
	getchar();

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
			execl("./crt","crt",childarg1_crt, childarg2_crt, (char *)0);
			fprintf(stderr, "Can't exec crt, errno %d\n",errno);
			cleanup();
			exit(1);
		}
	}
	sleep(1);

	printf("\nType something followed by end of line and it will be echoed \n\n");
}
