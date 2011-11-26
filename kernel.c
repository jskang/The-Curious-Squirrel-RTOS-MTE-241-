#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <setjmp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "rtx.h"
#include "init.h"
#include "userProcesses.h"

pcb *current_process; //global variables

pcb_queue *priority_ready_queue[4];
pcb_queue *blocked_message_envelope;
pcb_queue *blocked_message_receive;
pcb_queue *sleep_queue;
pcb_queue *i_process_queue;

int wall_clock_flag = 0;
msg_queue *all_envelopes;
msg_queue *free_envelopes;


long number_messages_sent;
long time_since_init;
int k_second;
int k_minute;
int k_hour;
msg_trace_buffer *message_buffer;

pcb* pcbList[TEMP_NUM_PROCESS];

iobuf *in_mem_p_kbd, *out_mem_p_crt;

int main (void){

	init();
	printf("initialization complete \n");
	pcb* first_process;
	first_process = rpq_dequeue();
	printf("first process selected \n");
	printf("%d \n",first_process->pid);
	current_process = first_process;
	longjmp(first_process->jbdata,1);
	printf("should not reach here \n");
	return EXIT_SUCCESS;

}
