#include <stdio.h>
#include "queues.h"
#include "rtx.h"
#include "primitives.h"
#include "testing functions.h"
int main () {
    // insert code here...
	/*pcb_queue *queue1;
	queue1 = (pcb_queue*)malloc(sizeof(pcb_queue));*/
	
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
	send_message((i%10), message_1);
		
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
		received= receive_message();
		printf("the first message in pcb=1 is :\n");
		print_msg(received);
		printf("pcb1 now has an inbox of:\n");
		print_msg_queue(current_process->inbox);
		printf("pcb1 now has a status of:%i\n",current_process->state);
	}
	
	
	
	printf("enter any key to continue\n");
	getchar();
    return 0;
}
