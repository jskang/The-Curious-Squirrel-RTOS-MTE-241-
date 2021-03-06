#include <string.h>

#include "kbcrt.h"
#include "rtx.h"
#include "iproc.h"
#include "atomic.h"
#include "primitives.h"

void kbd_i_process (){	
	atomic(ON);
	current_process->state = INTERRUPTED;
	pcb *temp_pcb = current_process;
	current_process =(pcb*) pcb_pointer(PID_I_PROCESS_KBD);
	if (in_mem_p_kbd->ok_flag == 1){
		if (current_process->inbox->head != NULL){
		
			//message envelope that points to the message
			Msg_Env *in_message = NULL;
		
			//get the pointer to the received message
			in_message =(Msg_Env*)k_receive_message();
			
			//copy the buffer to the message and send it
			
			strcpy(in_message->message, in_mem_p_kbd->indata);
			/*int i;
			for(i=0;i<in_message->size;i++){
				in_message->message[i]=in_mem_p_kbd->indata[i];
			}*/
			//in_message->message[0]= 'h';
			//printf("actual message --> %s\n\n",in_message->message[0]);
			in_message->size = in_mem_p_kbd->length;
			

			in_message->message_type =  M_TYPE_MSG_ACK;
			k_send_message(in_message->sender_id,in_message);

			//reset the buffer
			strcpy(in_mem_p_kbd->indata,"");
			in_mem_p_kbd->ok_flag = 0;
			in_mem_p_kbd->length = 0;
		}
	}
	
	current_process = temp_pcb;
	current_process->state = RUNNING; 
	atomic(OFF);
}


void crt_i_process(){

	atomic(ON);
	current_process->state = INTERRUPTED;
	pcb *temp_pcb = current_process; 
	current_process = (pcb*)pcb_pointer(PID_I_PROCESS_CRT); 			
	// Check if flag from crt u-process is true.
	
	if(out_mem_p_crt->ok_flag == 0){
		//printf("flag is on \n");
		if(current_process->inbox->head != NULL){	
			Msg_Env *out_message;
			// Receive and store the message into message envelope.
			out_message =(Msg_Env*) k_receive_message();
			// Need to dequeue message form the message queue.
			
			strcpy(out_mem_p_crt->indata, out_message->message);
			out_mem_p_crt->length = out_message->size;
			out_mem_p_crt->ok_flag = 1;
			
			// Send acknowledgement message.
			out_message->message_type =  M_TYPE_MSG_ACK;
			strcpy(out_message->message,"");
			out_message->size =0;
			//out->message->flag = 
			k_send_message(out_message->sender_id,out_message);
				
		}
	}
	current_process = temp_pcb;
	current_process->state = RUNNING; 
	atomic(OFF);
}
