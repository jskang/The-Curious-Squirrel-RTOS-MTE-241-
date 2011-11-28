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
		printf("Number of Msg_env in inbox: %i\n",number_of_messages(to_print));
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
		printf("Message[0] -> %i\n",to_print->message[0]);
		
		//printf("flag --> %i\n\n",to_print->flag);
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


void print_trace_buffer_msg(Msg_Env *message){
	if(message == NULL){
		printf("message for trace buffer is NULL");
		return;
	}
	printf("the trace buffer message conatins the following content\n");
	int i;
	for(i=0;i<(message->size/4);i++){
		printf("Message %i:\n",i);
		printf("---------------------------------\n");
		printf("sender id:%i\n",message->message[i*4]);
		printf("receiver id:%i\n",message->message[i*4 +1]);
		printf("time stamp%i\n",message->message[i*4 +2]);
		printf("m_type:%i\n",message->message[i*4 +3]);
	}
	return;
	
	
}

void print_rps(Msg_Env *message){//print results from request process status
	int i;
	printf("Process Status gives the following:\n");
	for (i=0;i<9;i++){
		printf("PID-> %i\n",message->message[i*3]);
		printf("State-> %i\n",message->message[i*3 +1]);
		printf("Priority-> %i\n",message->message[i*3+2]);	
	}

}


int number_of_messages(pcb *to_print){
	int i=0;
	Msg_Env *Q = to_print->inbox->head;
	while(Q != NULL){
		i++;
		Q=Q->next;
	}
	return 1;
	
}


int number_of_messages_2(msg_queue *to_print){
	int i=0;
	Msg_Env *Q = to_print->head;
	while(Q != NULL){
		i++;
		Q=Q->next;
	}
	return 1;
	
}

