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


void crt_i_process(){

	// Switch the current process.
	current_process->state = INTERRUPTED;
	pcb temp_pcb = current_process; 
	//current_process =	 (need to set the crt_i_process as the current process)
	
	// Create a message envelope.
	Msg_Env out_message;
	
	// Check if flag from crt u-process is true.
	if(out_mem_p_crt->ok_flag == 1){
		if(current_process->inbox != NULL){
			// Receive and store the message into message envelope.
			out_message = receive_message();
			// Need to dequeue message form the message queue.

			int i;			
			while(out_message->message[i] != '/n'){
				out_mem_p_crt->indata[i] = out_message->message[i];
			
				// Swap owner and sender ids.
				out_message->sender_id = PID_I_PROCESS_CRT;
				out_message->owner_id = out_message->sender_id;
				
				// Send acknowledgement message.
				out_message->message_type =  M_TYPE_MSG_ACK;
				send_message(out_message->owner_id,out_message);
				
				// Reset flag.
				out_mem_p_crt->ok_flag = 0; 
				i++;
			}
		}
	}
}