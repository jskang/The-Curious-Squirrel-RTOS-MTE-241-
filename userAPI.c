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
