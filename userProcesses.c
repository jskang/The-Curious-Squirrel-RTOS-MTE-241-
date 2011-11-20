#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"
#include "userProcesses.h"
#include "userAPI.h"

void processP(){

	const tWait = 500000;	// rcv loop wait time in usec, appriox value
	Msg_Env* env = msg_dequeue(pcbList[PID_PROCESS_P]->inbox);

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

void process_a(){
	Msg_Env *message;
	static int num = 0;

	do{
		message = request_msg_env();
		message->set_type(num);
		send(B_PID,message);
		num++;
		process_switch();
	}while (1);

}

void process_b(){
	Msg_Env *message;

	do{
		message = receive_message();
		send(C_PID,message);
		process_switch();
	}while(1);
}

void process_c(){
	Msg_Env *message;

	do{
		// check for message on local queue first
		message = local_dequeue();

		if (message == NULL){
			message = receive_message();
		}

		if ((message->get_type()) % 20 == 0){
			strcpy(message->data,"Process C\n");
			message->set_type(MSG);
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

void process_clock(){


}

void process_null(){

	do{
		process_switch();
	}while(1);

}
