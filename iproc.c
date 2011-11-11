#include <string.h>
#include "kbdcrt.h"
#include "rtx.h"
#include "atomic.h"
void kbd_i_process (){
	
	atomic(ON);
	if (current_process->inbox->head != NULL){
		//message envelope that points to the message
		Msg_Env *in_message;
		
		//get the pointer to the received message
		in_message = receive_message();

		//copy the buffer to the message and send it
		strcpy(in_mem_p_crt->indata, in_message->message);
		a = send_message(P_PROCESS,in_message);

		//reset the buffer
		strcpy(in_mem_p_kbd->indata,"");
		in_mem_p_kbd->ok_flag = 0;
		in_mem_p_kbd->length = 0;
	}
	atomic(OFF);
}
