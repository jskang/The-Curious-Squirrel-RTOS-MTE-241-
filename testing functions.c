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
		printf("pcb == NULL\n");
	
	while(current_pcb != NULL){
		print_pcb(current_pcb);
		current_pcb = current_pcb->next;
	}
}

	