/*
 *  queueimplementation.c
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

// Error Codes
#include INVALID_PCB_POINTER -105;

#include "rtx.h"
#include <stdio.h>
#include <stdlib.h>

void initialize_queue(queue*Q)
{
  Q->head = NULL;	//queue start with zero elements
	Q->tail = NULL;
}

int empty_queue(queue *Q)
{
	if (Q->head == NULL)
		return 1;	//queue is empty
	else
		return 0;  //false queue is not empty
}

int enqueue(queue *Q, pcb *new_pcb)
{
	if(new_pcb == NULL)
		return -105;
		
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

//this will take first element out of the queue and return pointer to said element
*pcb dequeu(queue *Q) 
{
	pcb * front= Q->head;
	Q->head = Q->head->next;
	return front;
}

//this dequeue remove a specified process from the queue, pid of process which is to be removed is passed to this function
*pcb dequeu_selected_pcb(queue *Q, int desired_pcb)
{
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