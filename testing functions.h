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

void print_msg(Msg_Env *to_print);

void print_msg_queue(msg_queue *Q);

void print_rpq_test(pcb_queue *Q[]);