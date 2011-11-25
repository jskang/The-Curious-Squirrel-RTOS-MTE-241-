#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

wall_clock_flag = 0;

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

}

void process_cci(){

	printf("we are in CCI \n");

	Msg_Env *msg_env;                // allocates output message
	msg_env = allocate_msg_env();
	char msg_first_char;
	char msg_second_char;
	char usr_cmd[2];
	while(1){
/*
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
*/

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
	
	Msg_Env *msg_env = current_process->inbox->head;
	
	static char hour_buf[3];
	static char min_buf[3];
	static char sec_buf[2];
	printf("Getting here\n");
	
		
	/*char message[10] = "c 13:34:55";
	strcpy(msg_env->message,message);		
	printf("Geting past strcpy");
	/*	
	int i = 0;
	printf("Message: ");
	while(msg_env->message[i] != NULL)
		printf("%s\n",msg_env->message[i]);
	*/



/*	if (current_process->inbox->head !=NULL){
		printf("msg_env is NOT null\n");
		//input in the message of the form c hh:mm:ss<cr>
						    // c space between here
		int h1 = atoi(current_process->inbox->message[2]);
		int h2 = atoi(msg_env->message[3]); // colon between here
		int m1 = atoi(msg_env->message[5]);
		int m2 = atoi(msg_env->message[6]); // colon between here
		int s1 = atoi(msg_env->message[8]);
		int s2 = atoi(msg_env->message[9]);
		printf("Getting past atoi");	
		// now we're dealing with hhmmss
		// we know the time is legal from the cci

		k_second = 10*s1+s2;
		k_minute = 10*m1+m2;
		k_hour   = 10*h1+h2;
	
	}*/
	Msg_Env *temp_msg;
	do{
		request_delay(10,M_TYPE_MSG_DELAY,msg_delay); 	// send envelope using request delay message	
		temp_msg = receive_message();				// receive messages from timer_i_process 		
		if(msg_delay != NULL){
			printf("getting here\n");
//------------------------why do we check if the msg_env is null here?


			// bhavik's time algorithm ******************************************************

			k_second++; 	// increment by one k_second
			k_second = (k_second++)%60;
			if(k_second == 0) {			// check to increment k_minute 
				k_minute = (k_minute++)%60;
				if (k_minute == 0) {			// check to increment k_hour
					k_hour = (k_hour++)%60;
				}	
			} 

			// end bhavik's time algorithm **************************************************


			
			// prepare to send to crt
			
			// we need output here that takes the h m and s and puts it in an envelope 

			if(k_hour<10)
				sprintf(hour_buf, "0%d:", k_hour);
			else
				sprintf(hour_buf, "%d:", k_hour);
			if(k_minute<10)
				sprintf(hour_buf, "0%d:", k_minute);
			else
				sprintf(hour_buf, "%d:", k_minute);
			if(k_second<10)
				sprintf(hour_buf, "0%d", k_second);
			else
				sprintf(hour_buf, "%d", k_second);

			//load up the time into the message envelope

			msg_env->message[0] = hour_buf[1];
			msg_env->message[1] = hour_buf[2];
			msg_env->message[2] = hour_buf[3];
			msg_env->message[3] = min_buf[0];
			msg_env->message[4] = min_buf[1];
			msg_env->message[5] = min_buf[2];
			msg_env->message[6] = sec_buf[0];
			msg_env->message[7] = sec_buf[1];

			/*

			int cnt = 0;
			for (cnt; cnt <3; cnt++){
				msg_env->message[cnt] = hour_buf[cnt];
			}
			cnt=3;
			for (cnt; cnt <6; cnt++){
				msg_env->message[cnt] = min_buf[cnt];
			}
			cnt=6;
			for (cnt; cnt <8; cnt++){
				msg_env->message[cnt] = sec_buf[cnt];
			}

			*/
			
			msg_env->message[8] = "\n";
			
			// message envelope now contains 
			//
			// [0] -> h	
			// [1] -> h
			// [2] -> :
			// [3] -> m
			// [4] -> m
			// [5] -> :
			// [6] -> s
			// [7] -> s
			// [8] -> \n
			//

			if(msg_env->message_type == M_TYPE_WALL_CLOCK){  // display to CRT if true
				
				// send msg_envelope to crt.
				// check if wall_clock_flag allows output
//-------------------------------- if (wall_clock_flag)
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
