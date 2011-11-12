#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"

void processP(){
	printf("HIIIIIIIII");
	const tWait = 500000;	// rcv loop wait time in usec, appriox value
	Msg_Env* env = msg_dequeue( pcbList[PID_PROCESS_P]->inbox);

	do{
		get_console_chars(env);		// keyboard input.
		env = receive_message();
		
		while (env == NULL){
			usleep(tWait);
			env = (Msg_Env*) receive_message();
		}
		
		send_console_chars(env);	// CRT output, wait for acknowledgement.
		env = (Msg_Env*)receive_message();
		while(env == NULL){
			usleep(tWait);
			env = (Msg_Env*)receive_message();
		}
	}while(1);
}
