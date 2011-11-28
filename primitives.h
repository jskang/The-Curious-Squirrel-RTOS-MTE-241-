/*
 *  primitives.h
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include "rtx.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>

int k_send_message(char dest_process_id, Msg_Env *msg_envelope);					//good
	
Msg_Env *k_receive_message();														//good

int k_get_console_chars(Msg_Env *message_envelope );								//good

int k_send_console_chars(Msg_Env *message_envelope );								//good

Msg_Env *k_request_msg_env ();														//good but need to check with process switching

int k_release_msg_env ( Msg_Env *message_envelope );								//good

int k_request_process_status( Msg_Env * message_envelope );							//probably good

int k_terminate( );	

int k_change_priority(int new_priority, int target_process_id);							//probably good

int k_request_delay(int time_delay,char wakeup_code,Msg_Env *message_envelope);

int k_get_trace_buffers( Msg_Env * message_envelope);								//good

int k_release_processor();

void process_switch();

void context_switch(pcb* next_process);

