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

void timer_i_process(){
	
	atomic(ON); // Turn atomic on.
	// Save state of original process and switch to current process.
	current_process->state = INTERRUPTED;
	pcb *temp_pcb = current_process;
	current_process =  (pcb*)pcb_pointer(PID_I_PROCESS_CRT);
	
	time_since_init++;
	Msg_Env *msg_env = (Msg_Env*) k_receive_message();
	
	while(msg_env != NULL){
		
		// decrement the counters in the received messages.
		msg_env->time_stamp--;	
		
		if(msg_env->time_stamp == 0){    //What does the 0 mean here?
		
			// send the message flag back to the delayed process		
			k_send_message(msg_env->sender_id,msg_env);
			
			// Am I missing something here? 
			
			// set the flag to M_TYPE_MSG_DELAY_BACK
			msg_env->message_type = M_TYPE_MSG_DELAY_BACK;
			
		}
		msg_env = msg_env->next;
	}	
	
	// Return the back to the previous process.
	current_process = temp_pcb;
	current_process->state = RUNNING;
	atomic(OFF);
}
