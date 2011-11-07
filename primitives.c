/*
 *  primitives.c
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include "rtx.h"
#include <stdio.h>
#include <stdlib.h>

int request_message_env()
{
	
}

int send_message(int dest_process_id, MsgEnv *msg_envelope)
{
	if (msg_envelope == Null)
		return -101;									//INVALID_MESSAGE_PTR_ERROR
	if (dest_process_id < 0 || dest_process_id >9 )
		return -103;									//INVALID_PID_ERROR
	
	msg_envelope->sender_id = msg_envelope->owner_id;   //owner id becomes sender id
	msg_envelope->owned_id=dest_process_id;				//destination process is now the owner
	pcb *receiver= pcb_pointer(dest_process_id);		//gets the pointer to the receiving pcb
	enqueue(receiver->inbox, msg_envelope)				//adds envelope to the pcbs inbox
	
	if (receiver->state == 3){							//checks if process is blocked on receive
		receiver->state = 0;							//set state to ready 
		enqueue(ready_process_queue, receiver);			//adds process to ready process queue
	}
	
	//Add SENDER_PID, RECEIVER_PID, CURRENT_TIME to message trace.
	return 1;
}
MsgEnv* receive_message()
{
	/*if(current_process ->inbox == NULL){
		current_process->state = 3;							//sets state to blocked on receive
		enqueue(blocked_on_receive, current_process);		// adds to blocked on receive queue
		switch_process();								
	}*/
	if(current_process ->inbox == NULL){					//this code is only for initial implemantation
		current_process->state = 6;							//sets state to NO_BLK_RCV 
		return NULL;
	}
		
	MsgEnv *message_envelope = current_process->inbox;		//will this point to the first message?
	inbox->next = message_envelope->next;					//inbox now points to the next enelope,
	//could it be better to have this as a function?
	//Add SENDER_PID, RECEIVER_PID, CURRENT_TIME to message trace.
	
	return message_envelope;
}


int get_console_chars(MsgEnv * message_envelope )
{
	if(message_envelope = NULL)
		return return -101;								//INVALID_MESSAGE_PTR_ERROR
	
	send_message(7,message_envelope)					// sends message to kbd(7) 
	return 1;
}
	
int send_console_chars(MsgEnv * message_envelope )
{
	if(message_envelope = NULL)
		return return -101;								//INVALID_MESSAGE_PTR_ERROR
	/*if(message_envelope->flag == 3
	   return  INVALID_MESSAGE_TYPE*/
	send_message(6,message_envelope)					// sends message to crt(6) 
	return 1;
}

int release_msg_env ( MsgEnv * message_envelope )
{
	if(!empty_queue(blocked_on_resource_queue))
	{
		pcb *free_pcb= dequeue(blocked_on_resource_queue);		//gets first pcb from blocked_on_resource_queue
		free_pcb->state = 0										//sets state to this process to ready
		rpq_enqueue (free_pcb);
	}
	
}
	

int request_process_status( MsgEnv * memory_block )
{
	
}
	
int terminate( )
{
	
}
	
int change_priority(int new_priority, int target_process_id)
{
	
}
	
int request_delay(int time_delay,int wakeup_code,MsgEnv *message_envelope)
{
	
}
	
	
int get_trace_buffers( MsgEnv * message_envelope)
{
	
}
