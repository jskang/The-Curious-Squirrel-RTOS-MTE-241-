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
