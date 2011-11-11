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
#include "rtx.h"
/*
int request_message_env(){
	return 1;
}
*/
int send_message(int dest_process_id, Msg_Env *msg_envelope){
	if (msg_envelope == NULL){
		return INVALID_MESSAGE_PTR_ERROR;
	}

	if (dest_process_id < 0 || dest_process_id >9 ){        //checks validit of the p_id
		return INVALID_PID_ERROR;
	}

	msg_envelope->sender_id = msg_envelope->owner_id;		//owner id becomes sender id
	msg_envelope->owner_id = dest_process_id;					//destination process is now the owner
	pcb *receiver = pcb_pointer(dest_process_id);			//gets the pointer to the receiving pcb
	msg_enqueue(receiver->inbox, msg_envelope);				//adds envelope to the pcbs inbox

	if (receiver->state == BLOCKED_ON_RECEIVE){
		receiver->state = READY;
		rpq_enqueue(receiver);				//adds process to ready process queue
	}

	//Add SENDER_PID, RECEIVER_PID, CURRENT_TIME to message trace.
	return 1;
}

Msg_Env *receive_message()
{

	/*if(current_process ->inbox->head == NULL){
		current_process->state = 3;							//sets state to blocked on receive
		enqueue(blocked_on_receive, current_process);		// adds to blocked on receive queue
		switch_process();
	}*/

	if(current_process ->inbox->head == NULL){					//this code is only for initial implemantation
		current_process->state = NO_BLK_RCV;
		return NULL;
	}
	Msg_Env *message_envelope = msg_dequeue(current_process->inbox);
	//Add SENDER_PID, RECEIVER_PID, CURRENT_TIME to message trace.

	return message_envelope;
}


int get_console_chars(Msg_Env *message_envelope ){
	if(message_envelope == NULL)
		 return INVALID_MESSAGE_PTR_ERROR;
	send_message(PID_I_PROCESS_KBD, message_envelope);					// sends message to kbd(7) 
	return 1;
}

int send_console_chars(Msg_Env *message_envelope )
{
	if(message_envelope = NULL)
		return INVALID_MESSAGE_PTR_ERROR;								//INVALID_MESSAGE_PTR_ERROR
	/*if(message_envelope->flag == 3
	   return  INVALID_MESSAGE_TYPE*/
	send_message(PID_I_PROCESS_CRT ,message_envelope);					// sends message to crt(6) 
	return 1;
}
/*
int deallocate_msg_env ( Msg_Env *message_envelope )
{
	if(empty_pcb_queue(blocked_message_envelope)==0)
	{
		pcb *free_pcb= dequeue(blocked_message_envelope);		//gets first pcb that is blocked on resource
		free_pcb->state = READY;									//sets state to this process to ready
		rpq_enqueue (free_pcb);

	}
	//dequeue envelope from inbox of pcb?
	msg_enqueue(free_envelopes,message_envelope);
	return 1;
}


int request_process_status( Msg_Env * message_envelope ){
	if (message_envelope == NULL)
		return INVALID_MESSAGE_PTR_ERROR;
	pcb *current = all_pcbs->head;
	int i=0;
	do{																	//may switch this to a for loop
		message_envelope-> message[i]=current->pid;
		message_envelope-> message[i+1]=current->state;
		message_envelope-> message[i+2]=current->priority;
		current=current->pcb_all;
		i+=3;
	}while(current !=NULL);

	message_envelope->flag=M_TYPE_REQ_PROCESS_STATUS ;
	send_message(PID_I_PROCESS_CRT, message_envelope);
	return 1;
}

int terminate( ){
	return 1;
}

int change_priority(int new_priority, int target_process_id){
	if (target_process_id>9 || target_process_id<0)
		return INVALID_PID_ERROR;
	if (new_priority <0 || new_priority>2)								//2 as 3 is reserved for null process
		return INVALID_PRIORITY_ERROR;

	pcb *process = pcb_pointer(target_process_id);
	process->priority = new_priority;
	return 1;
}

int request_delay(int time_delay,int wakeup_code,Msg_Env *message_envelope){
	return 1;
}


int get_trace_buffers( Msg_Env * message_envelope){
	return 1;
}
*/

