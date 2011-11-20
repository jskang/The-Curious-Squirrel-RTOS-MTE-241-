#include <stdio.h>
#include "queues.h"
#include "rtx.h"
#include "primitives.h"
#include "testing functions.h"
long number_messages_sent=0;

int main () {
	/*pcb_queue *queue1;
	queue1 = (pcb_queue*)malloc(sizeof(pcb_queue));*/
	/*
	Msg_Env *message_1;
	pcb *pcb1;
	message_1 = (Msg_Env*)malloc(sizeof(struct Msg_Env));
	all_pcbs =(pcb_queue*)malloc(sizeof(struct pcb_queue));
	all_envelopes=(msg_queue*)malloc(sizeof(struct msg_queue));
	int i;
	initialize_queue(all_pcbs);
	for(i=0; i<10; i++)
	{
		pcb1 = (pcb*)malloc(sizeof(struct pcb));
		initialize_pcb(pcb1);
		pcb1->pid = i;
		pcb1->state = READY;
		pcb1->priority=(i%4);
	}
	print_all_pcb_queue();
	message_1->owner_id=1;
	
	for(i=0; i<20;i++){
		message_1 = (Msg_Env*)malloc(sizeof(struct Msg_Env));
		initialize_msg_env(message_1);
		message_1->owner_id=1;
		message_1->flag=i;	
		k_send_message((i%10), message_1);
		
	}

	print_all_pcb_inbox();
	
	printf("all the message envelopes are:\n");
	print_msg_all_queue();
   
	
	
	//now testing rthe receive primitive
	
	Msg_Env *received;
	current_process = pcb_pointer(1);		// current process = process with pid = 1
	
	
	for(i=0; i<20;i++){
		
		
		printf("\n\n\npcb1 has an inbox of:\n");
		print_msg_queue(current_process->inbox);
		received= k_receive_message();
		printf("the first message in pcb=1 is :\n");
		print_msg(received);
		printf("pcb1 now has an inbox of:\n");
		print_msg_queue(current_process->inbox);
		printf("pcb1 now has a status of:%i\n",current_process->state);
	}
	*/
	//initialize all the pcb queues which will be needed
	initialize_rpq_queue();
	blocked_message_envelope  = (pcb_queue*)malloc(sizeof(pcb_queue));
	initialize_queue(blocked_message_envelope);
	blocked_message_receive  = (pcb_queue*)malloc(sizeof(pcb_queue));
	initialize_queue(blocked_message_receive);
	
	
	//initialize all the msg envelope queues which will be needed
	all_envelopes=(msg_queue*)malloc(sizeof(struct msg_queue));
	initialize_msg_queue(all_envelopes);
	free_envelopes=(msg_queue*)malloc(sizeof(struct msg_queue));							
	initialize_msg_queue(free_envelopes);	
	message_buffer= (msg_trace_buffer*)malloc(sizeof(struct msg_trace_buffer));	
	initialize_msg_trace(message_buffer);
	
	initialize_queue(all_pcbs);
	int i;
	pcb *pcb1;
	
	for(i=0; i<9; i++)
	{
		
		pcb1 = (pcb*)malloc(sizeof(pcb));
		initialize_pcb(pcb1);
		pcb1->pid =i;
		pcb1->state = READY;
		pcb1->priority=i%3;
			pcbList[i]=pcb1;									//adds all to all pcb queuepcbs
	}

		rpq_enqueue(pcbList[0]);
		rpq_enqueue(pcbList[3]);
		rpq_enqueue(pcbList[6]);

	
	/*for(i = 0;i<TEMP_NUM_PROCESS;i++){
		pcbList[i] = (pcb*)(malloc(sizeof(pcb)));
		pcbList[i]->inbox = (msg_queue*)(malloc(sizeof(msg_queue)));
		if(pcbList[i] == NULL){
			return INVALID_QUEUE_ERROR;
		}
		pcbList[i]->pid = i;
		pcbList[i]->state = READY;
		pcbList[i]->priority = i%3;
		pcbList[i]->next = NULL;
		pcbList[i]->inbox->head = NULL;
		pcbList[i]->inbox->tail = NULL;
	}*/

	print_all_pcb_queue();
	//print_rpq();
	printf("pcbs with priority 0 are:\n");
	print_pcb_queue(priority_ready_queue[0]);
	printf("pcbs with priority 1 are:\n");
	print_pcb_queue(priority_ready_queue[1]);
	printf("pcbs with priority 2 are:\n");
	print_pcb_queue(priority_ready_queue[2]);
	/*Msg_Env *message_1;
	
	for(i=0; i<9;i++){
		message_1 = (Msg_Env*)malloc(sizeof(struct Msg_Env));
		initialize_msg_env(message_1);
		message_1->owner_id=1;
		message_1->flag=i;
		msg_enqueue(free_envelopes,message_1);
		msg_enqueue_all(message_1);
		
	}

	current_process = rpq_dequeue();
	printf("the pcb requesting envelopes is %i:\n",current_process->pid);
	print_pcb(current_process);
	printf("pcbs with priority 0 are:\n");
	print_pcb_queue(priority_ready_queue[0]);
	
	for(i=0;i<12;i++){
		message_1 = k_allocate_msg_env();
		printf("now allocating message\n");
		print_msg(message_1);
		msg_enqueue(current_process->inbox,message_1);
	}
	printf("pcb_queue blocked on message envelope is now \n");
	print_pcb_queue(blocked_message_envelope);
	printf("current_process has an inbox of \n");
	print_msg_queue(current_process->inbox);
	
	printf("now some message envelopes will be removed from the current process\n");
	for(i=0;i<6;i++){
		
		message_1 = msg_dequeue(current_process->inbox);
		printf("now deallocating message\n");
		print_msg(message_1);
		k_deallocate_msg_env(message_1);
	}
	
	printf("pcb_queue blocked on message envelope is now \n");
	print_pcb_queue(blocked_message_envelope);
	printf("current_process has an inbox of \n");
	print_msg_queue(current_process->inbox);
	printf("now looking at ready process queue\n");
	printf("pcbs with priority 0 are:\n");
	print_pcb_queue(priority_ready_queue[0]);
	printf("pcbs with priority 1 are:\n");
	print_pcb_queue(priority_ready_queue[1]);
	printf("pcbs with priority 2 are:\n");
	print_pcb_queue(priority_ready_queue[2]);
	
	
	//now testing request process status
	message_1 = msg_dequeue(current_process->inbox);
	k_request_process_status(message_1);
	pcb1=pcb_pointer(PID_I_PROCESS_CRT);
	message_1 = msg_dequeue(pcb1->inbox);
	print_message(message_1);
	
	*/
	
	
	
	printf("enter any key to continue\n");
	getchar();
    return 0;
}
