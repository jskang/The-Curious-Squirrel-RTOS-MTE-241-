/*
 *  testing functions.h
 *  main
 *
 *  Created by Markus Trapp on 11-11-09.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "queues.h"

void print_pcb_queue(pcb_queue *Q);

void print_pcb(pcb *to_print);

void print_all_pcb_queue();

void print_msg(Msg_Env *to_print);

void print_msg_queue(msg_queue *Q);

void print_msg_all_queue();

void print_rpq_test(pcb_queue);

void print_pcb_inbox(pcb *to_print);

void print_all_pcb_inbox();

void print_message(Msg_Env *message);

void print_trace_buffer();
	
void print_trace_buffer_msg(Msg_Env *message);

void print_rps(Msg_Env *message);

int number_of_messages(pcb *to_print);

int number_of_messages_2(msg_queue *to_print);