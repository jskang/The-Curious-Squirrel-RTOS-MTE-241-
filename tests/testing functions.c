/*
 *  testing functions.c
 *  main
 *
 *  Created by Markus Trapp on 11-11-09.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include "testing functions.h"

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
	
	pcb *current_pcb = Q->head;
	
	if(current_pcb == NULL)
		printf("pcb_queue == NULL\n");
	
	while(current_pcb != NULL){
		print_pcb(current_pcb);
		current_pcb = current_pcb->next;
	}
}

void print_all_pcb_queue(){
	
	pcb *current_pcb = all_pcbs->head;
	
	if(current_pcb == NULL)
		printf("pcb_queue == NULL\n");
	
	while(current_pcb != NULL){
		print_pcb(current_pcb);
		current_pcb = current_pcb->pcb_all;
	}
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
		printf("flag --> %i\n\n",to_print->flag);
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

void print_all_pcb_inbox(){
	if (all_pcbs==NULL)
		return;
	pcb *current=all_pcbs->head;
	while(current!=NULL){
		printf("pcb_id ==%i has the following messages in its inbox:\n",current->pid);
		print_pcb_inbox(current);
		current=current->pcb_all;
	}
		
	printf("end of inboxes\n");
}
	
