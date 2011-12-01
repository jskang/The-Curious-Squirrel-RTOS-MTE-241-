#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

void process_a(){
	printf("PROCESS A \n");
	Msg_Env *tmp_msg;
	static int num = 0;
	tmp_msg = receive_message();
	release_msg_env(tmp_msg);

	do{
		tmp_msg = request_msg_env();
		tmp_msg->message_type = M_TYPE_COUNT_REPORT;
		tmp_msg->message[1] = num;
		send_message(PID_PROCESS_B,tmp_msg);
		num++;
		release_processor();
	}while (1);

}

void process_b(){
	printf("PROCESS B \n");
	Msg_Env *tmp_msg;

	do{
		tmp_msg = receive_message();
		send_message(PID_PROCESS_C,tmp_msg);
		release_processor();
	}while(1);
}

void process_c(){
	printf("PROCESS C \n");
	Msg_Env* tmp_msg;
	msg_queue* local_msg_queue;
	local_msg_queue = (msg_queue*) malloc(sizeof(msg_queue));

	do{
		// check for message on local queue first
		tmp_msg =(Msg_Env*) msg_dequeue(local_msg_queue);

		if (tmp_msg == NULL){
			tmp_msg = receive_message();
		}

		if (tmp_msg->message_type == M_TYPE_COUNT_REPORT){
			if ((tmp_msg->message[1]) % 20 == 0){
				strcpy(tmp_msg->message,"Process C\n");
				tmp_msg->message_type = M_TYPE_DEFAULT;
				send_console_chars(tmp_msg);
				tmp_msg = receive_message();
				while( tmp_msg->message_type != M_TYPE_MSG_ACK){
					msg_enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
					tmp_msg = receive_message();
				}
				request_delay(100, M_TYPE_MSG_DELAY_BACK, tmp_msg); // 1000 = 10 seconds
				tmp_msg = receive_message();
				while(tmp_msg->message_type != M_TYPE_MSG_DELAY_BACK){
					msg_enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
					tmp_msg = receive_message();
				}
			}
		}
		release_msg_env(tmp_msg);
		release_processor();
	}while(1);

}

void process_cci(){

	Msg_Env *msg_env;                // allocates output message
	Msg_Env *out_env;
	Msg_Env *send;
	char usr_cmd[2];
	out_env = request_msg_env();
	msg_env = request_msg_env();
	while(1){
		
		out_env->message_type = M_TYPE_COMMANDS;	
		strcpy(out_env->message,"\033[35mCCI:\033[0m ");
		send_console_chars(out_env);
		out_env = receive_message();
		get_console_chars(msg_env);
		msg_env = receive_message();
	
		strncpy(usr_cmd,msg_env->message,2);	// store the user command.
		
		if(msg_env->size < 12){
			if(strncmp(usr_cmd,"s",2) == 0){
				send = request_msg_env();
				send->message_type= M_TYPE_COMMANDS;
				send_message(PID_PROCESS_A, send);
				send = NULL;
			}
			else if(strncmp(usr_cmd,"ps",2) == 0){
				request_process_status(out_env);	// request process status (message envelope)
				out_env->message_type = M_TYPE_REQ_PROCESS_STATUS; 	
				send_console_chars(out_env);
				out_env = receive_message();
			}
			else if(strncmp(usr_cmd,"c ",2) == 0){
				if(msg_env->size == 10){
					// having a size of eleven means c (1) space (2) hh:mm:ss (7) enter (1) - > 11 total
					int hh, mm, ss;
					char c1, c2;
					if((sscanf(msg_env->message, "%*s %d %c %d %c %d", &hh, &c1, &mm, &c2, &ss)) == 5){
						// check for valid time	
						if ((hh <= 23) && (ss <= 59) && (mm <= 59) && (c1 == ':') && (c2 == ':') ){
							k_second = ss;
							k_minute = mm;
							k_hour = hh;
						}
						else{ 
							strcpy(out_env->message,"Invalid Time\n");
							out_env->message_type = M_TYPE_COMMANDS;
							send_console_chars(out_env);
							out_env = receive_message();
						}			
					}
				}
				else {
					strcpy(out_env->message,"Invalid Time \n");
					out_env->message_type = M_TYPE_COMMANDS;
					send_console_chars(out_env);
					out_env = receive_message();
				}

			}
			else if(strncmp(usr_cmd,"cd",2) == 0){
				
				// set wall_clock_flag to one permitting the output of the wall clock
				wall_clock_flag = 1;
			}
			else if(strncmp(usr_cmd,"ct",2) == 0){
				// set wall_clock_flag to zero denying the output of the wall clock
				wall_clock_flag = 0;
				// again we should be able to run this without the bottom line
			}
			else if(strncmp(usr_cmd,"b",2) == 0){
				//display contents of trace display buffer
				get_trace_buffers(out_env);
				out_env->message_type = M_TYPE_MESSAGE_TRACE;
				send_console_chars(out_env);
				out_env = receive_message();
			}
			else if(strncmp(usr_cmd,"t",2) == 0){

				//release all resources acquired from linux
				terminate();	// terminate the process.
			}
			else if(strncmp(usr_cmd,"n ",2) == 0){
				int new_priority, process_id;
				if(sscanf(msg_env->message, "%*s %d %d", &new_priority, &process_id) == 2){
					
 					if((new_priority >= 0 && new_priority <= 3) && (process_id >= 3 && process_id <= 7)){

						int pChange = change_priority(new_priority,process_id);	// change priority of process.

						if (pChange == 1){
							sprintf(out_env->message,"Priority of %d Changed to %d\n",process_id,new_priority);
							out_env->message_type = M_TYPE_COMMANDS;
							send_console_chars(out_env);
							out_env = receive_message();
							
	 					}
						else{
							strcpy(out_env->message,"Priority could not be changed\n");
							out_env->message_type = M_TYPE_COMMANDS;
							send_console_chars(out_env);
							out_env = receive_message();
						}
					}
					else if (process_id == PID_PROCESS_NULL){
						strcpy(out_env->message,"Cannot change the priority of NULL PROCESS\n");
			        		out_env->message_type = M_TYPE_COMMANDS;
					        send_console_chars(out_env);
						out_env = receive_message();
					}
					else if (process_id == PID_I_PROCESS_CRT || process_id == PID_I_PROCESS_KBD || process_id == PID_I_PROCESS_TIMER){
						strcpy(out_env->message,"Cannot change the priority of I-Process\n");
					        out_env->message_type = M_TYPE_COMMANDS;
		        			send_console_chars(out_env);
						out_env = receive_message();
					}
					else{ 
						strcpy(out_env->message,"Invalid Input\n");
					        out_env->message_type = M_TYPE_COMMANDS;
					        send_console_chars(out_env);
						out_env = receive_message();
					}
				}
			}		
			else{
				strcpy(out_env->message, "Command Not Recognized \n");
				out_env->message_type=M_TYPE_COMMANDS;
				send_console_chars(out_env);
				out_env = receive_message();
			}	
			release_processor();
		}
	}
}

void process_clock(){

	Msg_Env *msg_delay = request_msg_env();
	Msg_Env *output_msg = request_msg_env();	

	do{	
		
		request_delay(10,M_TYPE_MSG_DELAY_BACK,msg_delay); // request delay message	
		do{
			msg_delay = receive_message();
			if (msg_delay->message_type == M_TYPE_MSG_ACK){
				output_msg = msg_delay;
			}
		} while(msg_delay->message_type != M_TYPE_MSG_DELAY_BACK);

		if(msg_delay != NULL){

			k_second = (k_second + 1)%60;
			if(k_second == 0) {			// check to increment k_minute 
				k_minute = (k_minute + 1)%60;
				if (k_minute == 0) {		// check to increment k_hour
					k_hour = (k_hour + 1)%24;
				}	
			} 

			
			if (wall_clock_flag){	// check to display on console
				output_msg->size = sprintf(output_msg->message,"\033[s\033[80;70H\033[33m%02d:%02d:%02d\033[0m\033[u",k_hour,k_minute,k_second);
				send_console_chars(output_msg);
			}			
		}
		// Where do I deallocate the message envelopes?
		release_processor();
	}while(1);
}

void process_null(){

	do{
		release_processor();
	}while(1);

}
