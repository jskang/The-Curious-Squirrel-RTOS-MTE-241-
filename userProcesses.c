#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

void process_a(){
printf("------------------------at process a-------------------\n");
	Msg_Env *tmp_msg;
	static int num = 0;
	tmp_msg = receive_message();
	deallocate_msg_env(tmp_msg);

	do{
		tmp_msg = allocate_msg_env();
		print_msg(tmp_msg);
		printf("made it past allocate_msg_env\n");
		tmp_msg->message_type = M_TYPE_DEFAULT;
		tmp_msg->message[1] = num;
		send_message(PID_PROCESS_B,tmp_msg);
		printf("made it past send message              message now looks like:\n");
		print_msg(tmp_msg);
		num++;
		release_processor();
	}while (1);


}

void process_b(){
	Msg_Env *tmp_msg;
printf("*****************************at process b************************\n");
print_pcb(current_process);
	do{
		tmp_msg = receive_message();
		printf("received a message\n");
		print_msg(tmp_msg);
		send_message(PID_PROCESS_C,tmp_msg);
		release_processor();
	}while(1);	
}

void process_c(){
/*	Msg_Env* tmp_msg;
	msg_queue* local_msg_queue;
	local_msg_queue = (msg_queue*) malloc(sizeof(msg_queue));

	do{
		// check for message on local queue first
		tmp_msg = dequeue(local_msg_queue);

		if (tmp_msg == NULL){
			tmp_msg = receive_message();
		}
		
		if ((tmp_msg->message[1]) % 20 == 0){
			strcpy(tmp_msg->message,"Process C\n");
			tmp_msg->message_type = M_TYPE_DEFAULT;
			send_console_chars(tmp_msg);
			tmp_msg = receive_message();
			while( tmp_msg->message_type != M_TYPE_MSG_ACK){
				enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
				tmp_msg = receive_message();
			}
			request_delay(1000,M_TYPE_MSG_DELAY_BACK, tmp_msg); // 1000 = 10 seconds
			tmp_msg = receive_message();
			while(tmp_msg->message_type != M_TYPE_MSG_DELAY_BACK){
				enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
				tmp_msg = receive_message();
			}
		}
		deallocate_msg_env(tmp_msg);
		release_processor();
	}while(1);
*/

	printf("########################at process c################################\n");
	print_rpq();
	release_processor();
}

void process_cci(){
	
	Msg_Env *msg_env;
	char msg_first_char;
	char msg_second_char;
	char usr_cmd[2];
	do{
		msg_env = (Msg_Env*) receive_message();	// receive message.
		
		// extract first and second character
		msg_first_char = msg_env->message[0];		
		msg_second_char = msg_env->message[1];		
	
		strncpy(usr_cmd,msg_env->message,2);	// store the user command.
		
		if(msg_env->size< 12){
			
			if(strncmp(usr_cmd,"s",2) == 0){
				send_message(PID_PROCESS_A, msg_env);	// send message to process A
			}
			else if(strncmp(usr_cmd,"ps",2) == 0){
				request_process_status(msg_env);	// request process status (message envelope)			
			}
			else if(strncmp(usr_cmd,"c",2) == 0){
				if(msg_env->size == 11){
					send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
				}			
			}
			else if(strncmp(usr_cmd,"cd",2) == 0){
				send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
			}
			else if(strncmp(usr_cmd,"ct",2) == 0){
				send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
			}
			else if(strncmp(usr_cmd,"b",2) == 0){
				get_trace_buffers(msg_env);				
			}
			else if(strncmp(usr_cmd,"t",2) == 0){
				terminate();	// terminate the process.
			}
			else if(strncmp(usr_cmd,"n",2) == 0){
				change_priority(msg_env->message[4],msg_env->message[2]);	// change priority of process.
			}
		}	
	}while(1);
}


void process_clock(Msg_Env *msg_env){

	extern k_second;
	extern k_minute;
	extern k_hour;
	Msg_Env *msg_delay = allocate_msg_env();
	
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
				send_console_chars(msg_env);
				
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
