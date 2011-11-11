/*
 *  queues.h
 *  main
 *
 *  Created by Markus Trapp on 11-11-07.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */


#include "rtx.h"


void initialize_queue(pcb_queue *Q);

int empty_pcb_queue(pcb_queue *Q);

int enqueue_all(pcb_queue *Q, pcb *new_pcb);		//used to add pcbs to the queue which contains all pcbs

int enqueue(pcb_queue *Q, pcb *new_pcb);

pcb *dequeue(pcb_queue *Q);

pcb *dequeue_selected_pcb(pcb_queue *Q, char desired_pcb);

pcb *pcb_pointer(char desired_pcb);

void initialize_msg_queue(msg_queue *Q);

int empty_msg_queue(msg_queue *Q);

int msg_enqueue_all (msg_queue *Q, Msg_Env *chain_mail);  //used to add Msg_Envs to the queue which contains all Msg_Env

int msg_enqueue(msg_queue *Q, Msg_Env *chain_mail);

Msg_Env *msg_dequeue(msg_queue *Q);

int delete_all_msg_queue (msg_queue *Q);

Msg_Env *dequeue_selected_envelope(msg_queue *Q, int desired_pcb);

int initialize_rpq_queue();

int rpq_enqueue (pcb *ready_pcb);

pcb* rpq_dequeue ();

