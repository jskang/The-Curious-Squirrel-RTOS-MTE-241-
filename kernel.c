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
#include "primitives.h"

pcb *current_process; //global variables

pcb_queue *priority_ready_queue[4];
pcb_queue *blocked_message_envelope;
pcb_queue *blocked_message_receive;
pcb_queue *i_process_queue;

int atomic_flag = 0;

int wall_clock_flag = 0;
msg_queue *all_envelopes;
msg_queue *free_envelopes;
msg_queue *timer_queue;

long number_messages_sent;
long time_since_init;
int k_second = 0;
int k_minute = 0;
int k_hour = 0;

msg_trace_buffer *message_buffer_send;
msg_trace_buffer *message_buffer_receive;

pcb* pcbList[TEMP_NUM_PROCESS];

iobuf *in_mem_p_kbd, *out_mem_p_crt;

int main (void){

	init();
	printf("initialization complete \n");
	pcb* first_process;
	first_process =(pcb*) rpq_dequeue();
	printf("first process selected \n");
	printf("%d \n",first_process->pid);
	current_process = first_process;
	longjmp(first_process->jbdata,1);
	printf("should not reach here \n");
	return EXIT_SUCCESS;
}
