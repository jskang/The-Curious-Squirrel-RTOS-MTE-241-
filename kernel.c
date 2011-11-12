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
#include "kbcrt.h"

pcb *current_process; //global variables
pcb_queue *all_pcbs_queue;
pcb_queue *blocked_on_resource_queue;
pcb_queue *blocked_on_receive_queue;
pcb_queue *interrupted_queue;
pcb_queue *sleep_queue;
pcb_queue *priority_ready_queue[4];
pcb_queue *all_pcbs;
pcb_queue *blocked_message_envelope;
pcb_queue *blocked_receive;
msg_queue *all_envelopes;
msg_queue *free_envelopes;
msg_queue *free_i_envelopes;

iobuf *in_mem_p_kbd, *out_mem_p_crt;

int main (void){

	init();

	return EXIT_SUCCESS;

}
