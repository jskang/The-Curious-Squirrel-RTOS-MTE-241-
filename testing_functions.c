/*
 *  testing functions.c
 *  main
 *
 *  Created by Markus Trapp on 11-11-09.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include "testing_functions.h"

void print_pcb(pcb *to_print){
	if(to_print == NULL)
		printf("PCB == NULL\n");
	else{
		printf("----PCB------\n");
		printf("pid --> %i\n",to_print->pid);
		printf("state --> %i\n",to_print->state);
		printf("priority --> %i\n\n",to_print->priority);
	}
		
		
	
}

void print_pcb_queue(pcb_queue *Q){
	
	pcb *current = Q->head;
	
	if(current == NULL)
		printf("pcb_queue == NULL\n");
	
	while(current != NULL){
		print_pcb(current);
		current= current->next;
	}
}

void print_all_pcb_queue(){
	int i;
	for(i=0;i<9;i++)
		print_pcb(pcbList[i]);
}
void print_msg(Msg_Env *to_print){
	if(to_print == NULL)
		printf("Msg_Env == NULL\n");
	else{
		printf("----Msg_env------\n");
		printf("owner_id --> %i\n",to_print->owner_id);
		printf("sender_id --> %i\n",to_print->sender_id);
		printf("time_stamp --> %i\n",to_print->time_stamp);
		printf("message_type --> %i\n",to_print->message_type);
		printf("flag --> %i\n\n",to_print->message_type);
	}
	
	
	
}

void print_msg_queue(msg_queue *Q){
	
	Msg_Env *current_msg = Q->head;
	
	if(current_msg == NULL)
		printf("msg_queue == NULL\n");
	
	while(current_msg != NULL){
		print_msg (current_msg);
		current_msg = current_msg->next;
	}
}


void print_msg_all_queue(){
	if(all_envelopes == NULL){
		printf("the queue is gone\n");
		return;
	}
	Msg_Env *current_msg	= all_envelopes->head;
	
	if(current_msg == NULL)
		printf("msg_queue == NULL\n");
	
	while(current_msg != NULL){
		print_msg (current_msg);
		current_msg = current_msg->env_all;
	}
}


void print_rpq(){
	int i;
	for(i=0; i<4;i++){
		printf("------------------------------------\n");
		printf("PCBs with priority =%i\n",i);
		print_pcb_queue(priority_ready_queue[i]);
	}
		
}

void print_pcb_inbox(pcb *to_print){
	if (to_print==NULL)
		printf("The PCB == NULL\n");
	else
		print_msg_queue(to_print->inbox);
}


void print_message(Msg_Env *message){
	if (message == NULL)
		return;
	int i;
	if(message->message_type == M_TYPE_REQ_PROCESS_STATUS){
		printf("Now printing request process status\n");
		for (i=0; i<message->size;i++){
			printf("----PCB------\n");
			printf("pid --> %i\n",message->message[i*3]);
			printf("state --> %i\n",message->message[i*3 +1]);
			printf("priority --> %i\n\n",message->message[i*3 +2]);		
		}
	}
}

	
