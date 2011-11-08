/*
 *  queueimplementation.c
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

/* Include Files and Libraries */
#include "rtx.h"
#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
/*all queues use these functions*/
void initialize_queue(queue *Q){
  	Q->head = NULL;	//queue start with zero elements
	Q->tail = NULL;
}

int empty_queue(queue *Q){
	if (Q->head == NULL)
		return 1;	//queue is empty
	else
		return 0;  //false queue is not empty
}


//here are pcb specific queue functions *//*
int enqueue(queue *Q, pcb *new_pcb){
	if(new_pcb == NULL)
		return INVALID_PCB_POINTER;
		
	if(empty_queue(Q)){		//if queue is currently empty head and tail point to same element
		Q->head == new_pcb;
		Q->tail == new_pcb;
	}
	else{
		new_pcb->next = NULL;
		Q->tail->next = new_pcb;    //pcb who is currently is at end now points to the new pcb
		Q->tail = new_pcb;			//tail points to new pcb
	}
	
	return 1;	
	
	}
}

//this will take first element out of the queue and return pointer to said element
*pcb dequeue(queue *Q){
	pcb *front= Q->head;
	Q->head = Q->head->next;
	return front;
}

//this dequeue remove a specified process from the queue, pid of process which is to be removed is passed to this function
*pcb dequeue_selected_pcb(queue *Q, int desired_pcb){
	pcb * current = Q->head;
	pcb *previous;
	int found=0;
	
	if(current->pid == desired_pcb){    // if desired pcb is the first element
		head = head->next;              // head points tonext element
		if(head->next == NULL)			// if desired pcb is the only element in the queue
			tail = NULL;
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
}

//this will return the pointer of a pcb specified by the id passed in (looks through the all_pcb_queue
*pcb pcb_pointer(int desired_pcb){
	pcb *current->all_pcb_queue->head;
	
	while(current->pid != desired_pcb)		//loops till desired pcb is found
		current=current->next;
	
	return current;
	
}

/************* here is where message envelope queue functions begin*******************/


int msg_enqueue(queue *Q, Msg_Env *chain_mail){
	if(chain_mail == NULL)
		return INVALID_PCB_POINTER;
	
	if(empty_queue(Q)){		//if queue is currently empty head and tail point to same element
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
*Msg_Env msg_dequeue(queue *Q){
	Msg_Env *front= Q->head;
	Q->head = Q->head->next;
	return front;
}

*Msg_Env dequeue_selected_envelope(queue *Q, int desired_pcb){
	pcb * current = Q->head;
	pcb *previous;
	int found=0;
	
	if(current->pid == desired_pcb){    // if desired pcb is the first element
		head = head->next;              // head points tonext element
		if(head->next == NULL)			// if desired pcb is the only element in the queue
			tail = NULL;
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
}

/***************here is where the code for the ready process queue starts************************************/

int rpq_enqueue (pcb *ready_pcb){
	if (ready_pcb == NULL)
		return INVALID_PID_ERROR;											
	if (ready_pcb ->state != READY)
		return INVALID_PCB_STATE_ERROR;
	
	enqueue(priority_ready_queue[ready_pcb->priority], ready_pcb);				//sends the queue of which has the priority of the pcb
	return 1;
}

*pcb rpq_dequeue (){
	if (ready_pcb == NULL)
		return INVALID_PID_ERROR;											
	if (ready_pcb ->state != READY)
		return INVALID_PCB_STATE_ERROR;
	
	int i=0;
	while(!empty_queue(priority_ready_queue[i]))							//loops until a queue level is found whch contains elements
		i++;
	return dequeue(empty_queue(priority_ready_queue[i]);
}



