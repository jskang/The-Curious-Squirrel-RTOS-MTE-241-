/*
 *  primitives.h
 *  
 *
 *  Created by Markus Trapp on 11-11-06.
 *  Copyright 2011 University Of waterloo. All rights reserved.
 *
 */

#include "rtx.h"
#include <stdio.h>
#include <stdlib.h>

int send_message(int dest_process_id, Msg_Env *msg_envelope);

Msg_Env *receive_message();

int get_console_chars(Msg_Env *message_envelope );

int send_console_chars(Msg_Env *message_envelope );

int deallocate_msg_env ( Msg_Env *message_envelope );

int request_process_status( Msg_Env * message_envelope );

int terminate( );

int change_priority(int new_priority, int target_process_id);

int request_delay(int time_delay,int wakeup_code,Msg_Env *message_envelope);

int get_trace_buffers( Msg_Env * message_envelope);