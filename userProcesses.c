#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

void process_a(){
	Msg_Env *tmp_msg;
	static int num = 0;

	do{
		tmp_msg = request_msg_env();
		tmp_msg->message_type(M_TYPE_DEFAULT);
		tmp_msg->message[1] = num;
		send_message(PID_PROCESS_B,tmp_msg);
		num++;
		release_processor();
	}while (1);

}

void process_b(){
	Msg_Env *tmp_msg;

	do{
		tmp_message = receive_message();
		send(PID_PROCESS_C,tmp_msg);
		release_processor();
	}while(1);
}

void process_c(){
	Msg_Env *tmp_msg;

	do{
		// check for message on local queue first
		message = local_dequeue;

		if (message == NULL){
			message = receive_message();
		}

		if ((message->) % 20 == 0){
			strcpy(message->data,"Process C\n");
			message->message_type(MSG);
			send_console_characters(message);
			message = receive_message();
			while( message->get_type() != MSG ){
				local_enqueue(message);  // save message on the local queue
				message = receive_message();
			}
			request_delay(1000, WAKEUP, message); // 1000 = 10 seconds
			message = receive_message();
			while( message->get_type() != WAKEUP){
				local_enqueue(message);  // save message on the local queue
				message = receive();
			}
		}
		release_msg_env(message);
		process_switch();
	}while(1);

}

void process_cci(){
	
	MsgEnv *msg_env;
	char msg_first_char[1];
	char msg_second_char[1];
	char msg_cmd[2];
	do{

		msg_env = (Msg_Env*) k_receive_message();	// receive message.
		// extract first and second character
		msg_first_char = msg_env->message[0];		
		msg_second_char = msg_env->message[1];		
		
		if(msg_env->size< 12){
		
			switch(strncpy(msg_cmd,msg_env->message,2){
			
				case 's':
					send_message(msg_env, PID_PROCESS_A);	// send message to process A
					break;
				
				case 'ps':
					request_process_status(msg_env);	// request process status (message envelope)
					break;
				
				case 'c':
					if(msg_env->size == 11){
						send_message(msg_env, PID_PROCESS_CLOCK);	// send message to clock process
					}
					break;
					
				case 'cd':
					send_message(msg_env, PID_PROCESS_CLOCK);	// send message to clock process
					break;
					
				case 'ct':
					send_mesasge(msg_env, PID_PROCESS_CLOCK);	// send message to clock process
					break;
					
				case 'b':
					get_trace_buffer(msg_env);	
					break;
					
				case 't':
					terminate();	// terminate the process.
					break;
					
				case 'n':
					if(msg_env->size == 5){
						change_priority(msg_env->message[4],msg_env->message[2]);	// change priority of process.
					}
					break;
					
				default
					break;	
			}
		}	
	}while(1);
}

void process_clock(MsgEnv *msg_env){

	extern k_second;
	extern k_minute;
	extern k_hour;
	MsgEnv *msg_delay = request_msg_env();
	
	do{

		request_delay(10,M_TYPE_MSG_DELAY,msg_delay); 	// send envelope using reques	t delay message	
		// receive messages from timer_i_process (how am I receiving the message? is it handled by send_message()?)
		
		if(msg_env != NULL){
			k_second++; 	// increment by one k_second
			k_second = (k_second++)%60;
			if(k_second == 0) {			// check to increment k_minute 
				k_minute = (k_minute++)%60;
				if (k_minute == 0) {			// check to increment k_hour
					k_hour = (k_hour++)%60;
				}	
			} 
			
			if(msg_env->message_type == M_TYPE_WALL_CLOCK){  // display to CRT if true
				
				// send msg_envelope to crt.
				k_send_console_chars(msg_env);
				
			}
			
		}
		
		release_processor();
	}while(1);

}

void process_null(){

	do{
		process_switch();
	}while(1);

}
