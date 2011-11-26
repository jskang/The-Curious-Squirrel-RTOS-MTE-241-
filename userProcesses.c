#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

void process_a(){
	Msg_Env *tmp_msg;
	static int num = 0;

	do{
		tmp_msg = allocate_msg_env();
		tmp_msg->message_type = M_TYPE_DEFAULT;
		tmp_msg->message[1] = num;
		send_message(PID_PROCESS_B,tmp_msg);
		num++;
		release_processor();
	}while (1);

}

void process_b(){
	Msg_Env *tmp_msg;

	do{
		tmp_msg = receive_message();
		send_message(PID_PROCESS_C,tmp_msg);
		release_processor();
	}while(1);
}

void process_c(){
	Msg_Env* tmp_msg;
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
				msg_enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
				tmp_msg = receive_message();
			}
			request_delay(1000,M_TYPE_MSG_DELAY_BACK, tmp_msg); // 1000 = 10 seconds
			tmp_msg = receive_message();
			while(tmp_msg->message_type != M_TYPE_MSG_DELAY_BACK){
				msg_enqueue(local_msg_queue,tmp_msg);  // save message on the local queue
				tmp_msg = receive_message();
			}
		}
		deallocate_msg_env(tmp_msg);
		release_processor();
	}while(1);

}

void process_cci(){

	printf("we are in CCI \n");

	Msg_Env *msg_env;                // allocates output message
	msg_env = allocate_msg_env();
	char msg_first_char;
	char msg_second_char;
	char usr_cmd[2];
	while(1){

		//get_console_chars(msg_env);
		printf("we are here 1\n");
		//msg_env = (Msg_Env*) receive_message();	// receive message.
		msg_env = allocate_msg_env();
		msg_env->size = 10;
		msg_env->message[0] = 'c';
		msg_env->message[1] = ' ';
		msg_env->message[2] = '1';
		msg_env->message[3] = '2';
		msg_env->message[4] = ':';
		msg_env->message[5] = '4';
		msg_env->message[6] = '7';
		msg_env->message[7] = ':';
		msg_env->message[8] = '5';
		msg_env->message[9] = '5';

		//printf("%s",msg_env->message);
		printf("we are here 2\n");
		
		// extract first and second character
		//msg_first_char = msg_env->message[0];		
		//msg_second_char = msg_env->message[1];	
	
		
		strncpy(usr_cmd,msg_env->message,2);	// store the user command.
		
		if(msg_env->size < 12){
			printf("getting here okay.\n");
			if(strncmp(usr_cmd,"s",2) == 0){
				printf("Sending message to Process A\n");
				send_message(PID_PROCESS_A, msg_env);	// send message to process A
				if (send_message(PID_PROCESS_A, msg_env))
					printf("Message Sent to Process A\n");
			}
			else if(strncmp(usr_cmd,"ps",2) == 0){
				//this portion should display the status of all the processes 
				//wint i=0;
				//printf("-----------------------------------");
				//for (i;i<10;i++){                               //loop through the processes
					//printf("%i \n",pcbList[i]->state);	
					printf("Requesting Status\n");	 
					request_process_status(msg_env);	// request process status (message envelope)
					if (request_process_status(msg_env))
						printf("Status Requested\n");	
				//}		
				//printf("-----------------------------------");
			}
			else if(strncmp(usr_cmd,"c ",2) == 0){

				printf("Inside the CCI WallClock\n");
				if(msg_env->size == 10){
					// having a size of eleven means c (1) space (2) hh:mm:ss (7) enter (1) - > 11 total
					int hh, mm, ss;
					char c1, c2;
					if((sscanf(msg_env->message, "%*s %d %c %d %c %d", &hh, &c1, &mm, &c2, &ss)) == 5){
						// check for valid time	
						if ((hh > 24) || (ss > 60) || (mm > 60) || (c1 != ':') || (c2 != ':'))
							printf("Invalid Time");
						else{ 
							printf("Got the correct time\n");
							k_second = ss;
							k_minute = mm;
							k_hour = hh;
							send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
					}			
				}
			}
		}
			else if(strncmp(usr_cmd,"cd",2) == 0){
				
				// set wall_clock_flag to one permitting the output of the wall clock
				wall_clock_flag = 1;

				// send message to the clock
				// we could hypothetically not use the bottom line of code which was originally here
				// send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
			}
			else if(strncmp(usr_cmd,"ct",2) == 0){

				// this should turn off the wall clock 
				// set wall_clock_flag to zero denying the output of the wall clock
				wall_clock_flag = 0;

				// again we should be able to run this without the bottom line
				// send_message(PID_PROCESS_CLOCK, msg_env);	// send message to clock process
			}
			else if(strncmp(usr_cmd,"b ",2) == 0){

				//display contents of trace display buffer
				get_trace_buffers(msg_env);				
			}
			else if(strncmp(usr_cmd,"t ",2) == 0){

				//terminate the fuck out of everything 
				//release all resources acquired from linux
				terminate();	// terminate the process.
			}
			else if(strncmp(usr_cmd,"n ",2) == 0){
				// get the new priority list

				//check if the process is a NULL process
				//we can't edit the NULL process
				//The arguments must be verified to ensure a valid process_id and priority level is given.
				if (msg_env->message[2] < 0 || msg_env->message[2] >3 || msg_env->message[4] < 0 || msg_env->message[4]>8 ){
					printf("Illegal Priority level");
					//break; //this will break the while loop
				}
				else if(current_process == NULL){
					printf("Trying to Edit NULL Process");
					//break; //this will break the while loop
				}
				else{ 
					int pChange = change_priority(msg_env->message[2],msg_env->message[4]);	// change priority of process.
					if (pChange)
						printf("Priority Changed to %i",msg_env->message[2]);
					else	
						printf("Priority could not be changed");
				}
			}
			else if (strncmp(usr_cmd,"xx",2) == 0){
				// this is a debugging test	
				printf("We are in the CCI test case");

			}
			else 
				printf("Command Not Recognized");
				//default error
				
		}	
		getchar();
		release_processor();
	}
}

void process_clock(){

	printf("ENTERING WALL CLOCK...\n");
	
	Msg_Env *msg_delay = allocate_msg_env();
	
	Msg_Env *output_msg = allocate_msg_env();	
	
	printf("Message envelopes have been allocated.\n");
	
	do{		
		printf("Attempting to request delay\n");
		request_delay(10,M_TYPE_MSG_DELAY,msg_delay); // request delay message	
		printf("Request delayed\n");		
		msg_delay = receive_message();	// receive messages from timer_i_process 		
		if(msg_delay != NULL){
			printf("Returning back after 1 second delay.\n");

			k_second++; 				// increment by one k_second
			k_second = (k_second++)%60;
			if(k_second == 0) {			// check to increment k_minute 
				k_minute = (k_minute++)%60;
				if (k_minute == 0) {		// check to increment k_hour
					k_hour = (k_hour++)%60;
				}	
			} 

			if(msg_delay->message_type == M_TYPE_WALL_CLOCK){  // display to CRT if true
				printf("Message type: WALL CLOCK\n");
				output_msg->size = sprintf(output_msg->message,"%d:%d:%d",k_hour,k_minute,k_second);				
				printf("Message stored in output_msg.\n");
				if (wall_clock_flag){	// check to display on console
					send_console_chars(output_msg);
				}				
			}			
		}
		// Where do I deallocate the message envelopes?
		deallocate_msg_env(msg_delay);
		deallocate_msg_env(output_msg);	
		release_processor();
	}while(1);
}

void process_null(){

	do{
		release_processor();
	}while(1);

}
