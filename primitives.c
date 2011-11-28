/*
 *  primitives.c
 *
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtx.h"
#include "primitives.h"
#include "queues.h"
#include "atomic.h"
#include "iproc.h"
#include "init.h"

int k_send_message(char dest_process_id, Msg_Env *msg_envelope){
	if (msg_envelope == NULL){
		return INVALID_MESSAGE_PTR_ERROR;
	}

	if (dest_process_id < 0 || dest_process_id >9 ){        //checks validit of the p_id
		return INVALID_PID_ERROR;
	}

	pcb *receiver = pcb_pointer(dest_process_id);		//gets the pointer to the receiving pcb
	if (receiver->state == BLOCKED_ON_RECEIVE){
		receiver = dequeue_selected_pcb(blocked_message_receive,dest_process_id);
		receiver->state = READY;
		rpq_enqueue(receiver);				//adds process to ready process queue
	}

	
	msg_envelope->sender_id = msg_envelope->owner_id; 	//owner id becomes sender id
	msg_envelope->owner_id = dest_process_id;		//destination process is now the owner
	msg_enqueue(receiver->inbox, msg_envelope);		//adds envelope to the pcbs inbox	
	enqueue_msg_trace(message_buffer_send,msg_envelope);
	
	return 1;
}

Msg_Env* k_receive_message(){

	Msg_Env *message_envelope = msg_dequeue(current_process->inbox);

	if(message_envelope == NULL && (current_process->pid == PID_I_PROCESS_CRT ||current_process->pid ==PID_I_PROCESS_KBD ||current_process->pid == PID_I_PROCESS_TIMER))
		return NULL;


	if(message_envelope == NULL){
		current_process->state = BLOCKED_ON_RECEIVE;	//sets state to blocked on receive
		enqueue(blocked_message_receive, current_process);	// adds to blocked on receive queue
		process_switch();
		message_envelope = msg_dequeue(current_process->inbox);
	}
	enqueue_msg_trace(message_buffer_receive,message_envelope);

	return message_envelope;
}


int k_get_console_chars(Msg_Env *message_envelope ){
	if(message_envelope == NULL)
		 return INVALID_MESSAGE_PTR_ERROR;
	k_send_message(PID_I_PROCESS_KBD, message_envelope);					// sends message to kbd(7) 
	return 1;
}

int k_send_console_chars(Msg_Env *message_envelope){
	if(message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;									//INVALID_MESSAGE_PTR_ERROR
	/*if(message_envelope->flag == 3
	   return  INVALID_MESSAGE_TYPE*/
	k_send_message(PID_I_PROCESS_CRT ,message_envelope);	// sends message to crt(6) 
	crt_i_process();	
	return 1;
}

Msg_Env *k_allocate_msg_env (){
	while(empty_msg_queue(free_envelopes) == 1){				//while there are no free envelopes available

			current_process->state= BLOCKED_ON_RESOURCE;
			enqueue(blocked_message_envelope, current_process);	//adds this process to blocked on resource queue
			process_switch();					//when this process eventually runs again it will start here
		}									//exits loop once there is an envelope available for process

	
	
	Msg_Env *message_envelope = msg_dequeue(free_envelopes);
	strcpy(message_envelope->message,"");
	message_envelope->message_type = M_TYPE_EMPTY;
	message_envelope->size = 0;
	message_envelope->time_stamp = 0;
	message_envelope->sender_id = 0;
	message_envelope->owner_id = current_process->pid;
	return message_envelope;
}

int k_deallocate_msg_env ( Msg_Env *message_envelope ){					//make sure when using this that the pcb no longer owns msg_env
	if (message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;
	if(empty_pcb_queue(blocked_message_envelope)==0)						//if there is an process blocked on resource
	{
		pcb *free_pcb= dequeue(blocked_message_envelope);					//gets first pcb that is blocked on resource
		free_pcb->state = READY;											//sets state to this process to ready
		rpq_enqueue (free_pcb);

	}
	msg_enqueue(free_envelopes,message_envelope);
	return 1;
}


int k_request_process_status( Msg_Env *message_envelope ){
	
	if (message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;
	int i=0;
	char temp_string[27];	// Added random numer for now.
	strcpy(message_envelope->message, "PID     State     Priority\n");
	strcpy(temp_string,"---     -----     --------\n");
	strcat(message_envelope->message,temp_string);		
	for(i=0;i<9;i++){
		sprintf(temp_string,"%2d%9d%12d\n",
					pcbList[i]->pid,
					pcbList[i]->state,
					pcbList[i]->priority);
		strcat(message_envelope->message,temp_string);
	}


	message_envelope->message_type = M_TYPE_REQ_PROCESS_STATUS ;			//sets the flag on envelope
	return 1;
}


int k_terminate( ){
	int i;
	Msg_Env* temp_msg;
	for (i = 0; i <9; i++){
		free(pcbList[i]->inbox);
		free(pcbList[i]);
	}

	for (i = 0; i < 4; i++){
		free(priority_ready_queue[i]);
	}
	
	temp_msg = msg_dequeue(all_envelopes);

	do{
		free(temp_msg);
		temp_msg = msg_dequeue(all_envelopes);

	}while(temp_msg != NULL);

	free(blocked_message_envelope);
	free(blocked_message_receive);
	free(i_process_queue);

	free(timer_queue);
	free(all_envelopes);
	free(free_envelopes);

	cleanup();
	exit(1);	
	return 1;
}

int k_change_priority(int new_priority, int target_process_id){
	if (target_process_id > 9 || target_process_id < 0)
		return INVALID_PID_ERROR;

	if (new_priority < 0 || new_priority > 2)								//2 as 3 is reserved for null process
		return INVALID_PRIORITY_ERROR;

	pcb *process = pcb_pointer(target_process_id);						
	if (process->state == READY){										//incase the pcb is already in the ready process queue
		rpq_dequeue_specific_pcb(process);
		process->priority = new_priority;
		rpq_enqueue(process);
	}
		
	else
		process->priority = new_priority;
	
	return 1;
}

int k_request_delay(int time_delay,char wakeup_code,Msg_Env *message_envelope){
	if (time_delay <= 0)
		return INVALID_TIME_DELAY;
	if(message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;
	//how are we doing wake up codes?

	
	message_envelope->message_type= M_TYPE_MSG_DELAY;	
	message_envelope->time_stamp = time_delay;
	message_envelope->message[0] = wakeup_code;	//i_timer should know how to respond to this
	if(k_send_message(PID_I_PROCESS_TIMER, message_envelope) != 1){
		return -1;
	}

	return 1;
}

int k_get_trace_buffers( Msg_Env * message_envelope){
	if(message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;
	
	message_envelope->message_type = M_TYPE_MESSAGE_TRACE ;
	char temp_string[74];	// Added random numer for now.
	int i;
	
	strcpy(message_envelope->message,"-- Sent Messages -- \n");
	strcpy(temp_string, "Message ID     Sender ID     Receiver ID     Time Stamp     Message Type\n");		
	strcat(message_envelope->message,temp_string);

	for (i = 0; i < 16; i++){
		sprintf(temp_string,"%6d%14d%16d%15ld%16d\n",(i+1),
		message_buffer_send->messages[i]->sender_PID,
		message_buffer_send->messages[i]->receiver_PID,
		message_buffer_send->messages[i]->time_stamp,
		message_buffer_send->messages[i]->m_type);
		strcat(message_envelope->message,temp_string);
	}

	strcpy(temp_string,"-- Received Messages -- \n");
	strcat(message_envelope->message,temp_string);
	strcpy(temp_string, "Message ID     Sender ID     Receiver ID     Time Stamp     Message Type\n");		
	strcat(message_envelope->message,temp_string);

	for (i = 0; i < 16; i++){					//loops 16 times
		sprintf(temp_string,"%6d%14d%16d%15ld%16d\n",(i+1),
		message_buffer_receive->messages[i]->sender_PID,
		message_buffer_receive->messages[i]->receiver_PID,
		message_buffer_receive->messages[i]->time_stamp,
		message_buffer_receive->messages[i]->m_type);
		strcat(message_envelope->message,temp_string);
	}		

	//fix this get the exact number of characters that are needed by the message envelope
	//message_envelope->size=64;
	return 1;
}

int k_release_processor(){
	current_process->state = READY;		//only use when putting back intot he rpq
	rpq_enqueue(current_process);
	process_switch();
	return 1;
}

void process_switch(){
	pcb* next_process; 
	next_process = rpq_dequeue();	//highest priority process in the ready process queue 
	atomic(ON);
	context_switch(next_process);
	atomic (OFF); 
}

void context_switch(pcb* next_process){

	if(setjmp(current_process->jbdata)==0){
		current_process = next_process;
		longjmp(next_process->jbdata,1);
	}	
	//current_process = next_process;	//note they have both been dequeued by this point

}
