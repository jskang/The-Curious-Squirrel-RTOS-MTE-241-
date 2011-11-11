#include <stdlib.h>
#include <stdio.h>
#include "rtx.h"

void processP(void){
  const tWait = 500000;	// rcv loop wait time in usec, approx value
	Msg_Env *env = request_message_env();
	while(1){
		get_console_chars(env);		// keyboard input.
		env = receive_message();
		while (env == NULL){
			usleep(twait);
			env = receive_message();
		}
		
		send_console_chars(env);	// CRT output, wait for acknowledgement.
		env = receive_message();
		while(env == NULL){
			usleep(twait);
			env = receive_message();
		}
	}
}