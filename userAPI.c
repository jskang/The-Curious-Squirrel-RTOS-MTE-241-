#include "primitives.h"
#include "atomic.h"
#include "userAPI.h"
#include "rtx.h"


int send_message(char dst_process_id, Msg_Env *msg_envelope){
	atomic(ON);
	int i;
	i = k_send_message(dst_process_id,msg_envelope);
	atomic(OFF);
	return i;
}

Msg_Env* receive_message(){
	atomic(ON);
	Msg_Env *temp;
	temp = k_receive_message();
	atomic(OFF);
	return temp;
}

int get_console_chars(Msg_Env *message_envelope){
	atomic(ON);
	int i;
	i = k_get_console_chars (message_envelope);
	atomic(OFF);
	return i;
}

int send_console_chars(Msg_Env *message_envelope){
	atomic(ON);
	int i;
	i = k_send_console_chars (message_envelope);
	atomic(OFF);
	return i;
}

Msg_Env* allocate_msg_env(){
	atomic(ON);
	Msg_Env *temp;
	temp = k_allocate_msg_env ();
	atomic(OFF);
	return temp;
}

int deallocate_msg_env (Msg_Env *message_envelope){
	atomic(ON);
	int i;
	i = k_deallocate_msg_env(message_envelope);
	atomic(OFF);
	return i;
}

int request_process_status (Msg_Env *message_envelope){
	atomic(ON);
	int i;
	i = k_request_process_status(message_envelope);
	atomic(OFF);
	return i;
}

int terminate(){
	atomic(ON);
	int i;
	i = k_terminate();
	atomic(OFF);
	return i;
}

int change_priority(int new_priority, int target_process_id){
	atomic(ON);
	int i;
	i = k_change_priority(new_priority, target_process_id);
	atomic(OFF);
	return i;
}

int request_delay(char time_delay, char wakeup_code, Msg_Env* message_envelope){
	atomic(ON);
	int i;
	i = k_request_delay(time_delay, wakeup_code, message_envelope);
	atomic(OFF);
	return i;
}

int get_trace_buffers(Msg_Env* message_envelope){
	atomic(ON);
	int i;
	i = k_get_trace_buffers(message_envelope);
	atomic(OFF);
	return i;
}

int release_processor(){
	atomic(ON);
	int i;
	i = k_release_processor();
	atomic(OFF);
	return i;
}


