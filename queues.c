/*
 *  queueimplementation.c
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

/* Include Files and Libraries */

#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
//here are pcb specific queue functions 

void initialize_queue(pcb_queue *Q){
  	Q->head = NULL;	//queue start with zero elements
	Q->tail = NULL;
}

int empty_pcb_queue(pcb_queue *Q){
	if (Q->head == NULL)
		return 1;						//queue is empty
	else
		return 0;						//false queue is not empty
}

int enqueue_all(pcb_queue *Q, pcb *new_pcb){
	if(new_pcb == NULL)
		return INVALID_PCB_POINTER;
	if(empty_pcb_queue(Q)){		//if queue is currently empty head and tail point to same element
		Q->head = new_pcb;
		Q->tail = new_pcb;
	}
	else{
		new_pcb->pcb_all = NULL;
		Q->tail->pcb_all = new_pcb;    //pcb who is currently is at end now points to the new pcb
		Q->tail = new_pcb;			//tail points to new pcb
	}
	return 1;	
	
}

int enqueue(pcb_queue *Q, pcb *new_pcb){
	if(new_pcb == NULL)
		return INVALID_PCB_POINTER;
	new_pcb->next = NULL;		//makes sure that the new pcb doesnt point to anything else
	if(empty_pcb_queue(Q)){		//if queue is currently empty head and tail point to same element
		Q->head = new_pcb;
		Q->tail = new_pcb;
	}
	else{
		Q->tail->next = new_pcb;    //pcb who is currently is at end now points to the new pcb
		Q->tail = new_pcb;			//tail points to new pcb
	}
	return 1;	
	
}


//this will take first element out of the queue and return pointer to said element
pcb *dequeue(pcb_queue *Q){
	pcb *front= Q->head;
	Q->head = Q->head->next;
	
	if(Q->head == NULL)								//if the last item is being dequeued
		Q->tail==NULL;
	
	front->next == NULL;
	return front;
}

//this dequeue remove a specified process from the queue, pid of process which is to be removed is passed to this function
pcb *dequeue_selected_pcb(pcb_queue *Q, char desired_pcb){
	if(empty_pcb_queue(Q))
		return NULL;
	if(desired_pcb >9 || desired_pcb<0 )
		return NULL;
	
	pcb *current_pcb = Q->head;
	pcb *previous_pcb;
	int pcb_found=0;

	
	
	if(current_pcb->pid == desired_pcb)    // if desired pcb is the first element
		current_pcb=dequeue(Q);
	
	while (current_pcb != NULL && pcb_found==0){							//loops until found or looped throught the entire queue
		
		if(current_pcb->pid != desired_pcb)
		{
			previous_pcb = current_pcb;
			current_pcb = current_pcb->next;
		}
		
		
		if(current_pcb->pid == desired_pcb)									//fucking up somewhere here
		{
			pcb_found=1;
			previous_pcb->next = current_pcb->next;							//the one behind the one we remove point to the pcb after (jumps it)
			if(current_pcb->next == NULL)									//if the pcb we are looking for is the last pcb
				Q->tail=previous_pcb;										//sets tail to second last pcb
			current_pcb->next == NULL;										//current_pcb no longer looks at anything
		}	

		
	}
		return current_pcb;
	
}

/*//this function will delete (free all memory) of a desird queue
int delete_pcb_queue (pcb_queue *Q){
	pcb *current_pcb = Q->head;
	pcb *next_pcb;
	
	while(current_pcb != NULL){						//will loop until all elements of the queue are freed
		next_pcb = current_pcb;						//stores the next value of current_pcb so we dont lose the queue
		free(current_pcb);							//frees the pcb we are currently looking at
		current_pcb;
	}
	
	free(Q);										//frees the memory of the actual 
	
}*/

//this will return the pointer of a pcb specified by the id passed in (looks through the all_pcb_queue)
pcb *pcb_pointer(pcb_queue *Q, char desired_pcb){
	pcb *current_pcb=Q->head;
	int found =0;
	while (current_pcb != NULL && found ==0){							//loops until found or looped throught the entire queue
		if(current_pcb->pid == desired_pcb)
			found=1;
		
		if(current_pcb->pid != desired_pcb)
			current_pcb = current_pcb->next;

		
	}
	return current_pcb;
	
	
}

/************* here is where message envelope queue functions begin*******************/

void initialize_msg_queue(msg_queue *Q){
  	Q->head = NULL;	//queue start with zero elements
	Q->tail = NULL;
}

int empty_msg_queue(msg_queue *Q){
	if (Q->head == NULL)
		return 1;	//queue is empty
	else
		return 0;  //false queue is not empty
}

//add message envelopes to the queue which contains all envelopes used once
int msg_enqueue_all (msg_queue *Q, Msg_Env *chain_mail){
	if(chain_mail == NULL)
		return INVALID_MSG_POINTER;
	
	chain_mail->next=NULL;
	if(empty_msg_queue(Q)){						//if queue is currently empty head and tail point to same element
		Q->head == chain_mail;
		Q->tail == chain_mail;
	}
	
	else{
		chain_mail->env_all = NULL;
		Q->tail->env_all = chain_mail;				//message envelope who is currently is at end now points to the new message envelope
		Q->tail = chain_mail;					//tail points to new message envelope
	}
	
	return 1;	
}

int msg_enqueue(msg_queue *Q, Msg_Env *chain_mail){
	if(chain_mail == NULL)
		return INVALID_MSG_POINTER;
	
	chain_mail->next=NULL;
	if(empty_msg_queue(Q)){						//if queue is currently empty head and tail point to same element
		Q->head == chain_mail;
		Q->tail == chain_mail;
	}
	
	else{
		chain_mail->next = NULL;
		Q->tail->next = chain_mail;    //message envelope who is currently is at end now points to the new message envelope
		Q->tail = chain_mail;			//tail points to new message envelope
	}
	
	return 1;	
}

//this will take first element out of the queue and return pointer to said element
Msg_Env *msg_dequeue(msg_queue *Q){
	Msg_Env *front= Q->head;
	Q->head = Q->head->next;
	
	if(Q->head == NULL)
		Q->tail =NULL;								//if the last item is being dequeued
	
	front->next == NULL;
	return front;
}

/*//this function will delete (free all memory) of a desird msg_queue ONLY USED WHEN TERMINATING RTX
int delete_all_msg_queue (msg_queue *Q){
	if (Q== NULL)
		return INVALID_MSG_POINTER;
	
	Msg_Env *current_msg = Q->head;
	Msg_Env *next_msg;
	
	while(current_msg != NULL){									//will loop until all elements of the queue are freed
		if(current_msg->next !=NULL)
			return INVALID_MESSAGE_DELETE;						//CANT DELETE if the message is still owned by a pcb
		
		next_msg = current_msg->env_all;						//stores the next value of current_pcb so we dont lose the queue
		free(current_msg->owner_id);
		free(current_msg->sender_id);
		free(current_msg->time_stamp);
		free(current_msg->message_type);
		free(current_msg->flag);
		free(current_msg->message);
		free(current_msg);										//frees the pcb we are currently looking at
		current_msg = next_msg;						//goes to the next element
	}
	
	free(Q);										//frees the memory of the actual 
}*/

//may get rid of this does not seem like it is needed
/*Msg_Env *dequeue_selected_envelope(msg_queue *Q, int desired_pcb){
	Msg_Env * current = Q->head;
	Msg_Env *previous = NULL;
	int found=0;
	
	if(current->pid == desired_pcb){									// if desired pcb is the first element needs to be treated differently
		Q->head = current->next;										// head points tonext element
		if(current->next == NULL)											// if desired pcb is the only element in the queue
			Q->tail = NULL;
	}
	
	else{
		
		while (current!= NULL || found == 0){	// searches throught the queue until reaches the end or finds a pcb with p_id as its pid
			previous=current;
			current=current->next;
			
			if (current->pid==desired_pcb){		//if the desired pcb is at the tail of the
				previous->next=current->next;
				if(previous->next == NULL)		//if tail was pointing at the desired pcb tail now needs to point to the previous pcb
					Q->tail== previous;	
				found == 1;						//exits the loop
			}
		}
		
	}
	
	return current;
}*/

/***************here is where the code for the ready process queue starts************************************/
/*
int rpq_enqueue (pcb *ready_pcb){
	if (ready_pcb == NULL)
		return INVALID_PID_ERROR;											
	if (ready_pcb ->state != READY)
		return INVALID_PCB_STATE_ERROR;
	
	enqueue(priority_ready_queue[ready_pcb->priority], ready_pcb);				//sends the queue of which has the priority of the pcb
	return 1;
}

pcb* rpq_dequeue (){
	if (ready_pcb == NULL)
		return INVALID_PID_ERROR;											
	if (ready_pcb ->state != READY)
		return INVALID_PCB_STATE_ERROR;
	
	int i=0;
	while(!empty_queue(priority_ready_queue[i]))							//loops until a queue level is found whch contains elements
		i++;
	return dequeue(empty_queue(priority_ready_queue[i]);
}

*/

