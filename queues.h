/*
 *  queues.h
 *  main
 *
 *  Created by Markus Trapp on 11-11-07.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#define MAXQUEUESIZE 100
#include "rtx.h"


void initialize_queue(queue *Q);

int empty_queue(queue *Q);

int enqueue(queue *Q, pcb *new_pcb);

*pcb dequeue(queue *Q);

*pcb dequeue_selected_pcb(queue *Q, int desired_pcb);

*pcb pcb_pointer(int desired_pcb);

int msg_enqueue(queue *Q, Msg_Env *chain_mail);

*Msg_Env msg_dequeue(queue *Q);

*Msg_Env dequeue_selected_envelope(queue *Q, int desired_pcb);

int rpq_enqueue (pcb *ready_pcb);

*pcb rpq_dequeue ();
#endif