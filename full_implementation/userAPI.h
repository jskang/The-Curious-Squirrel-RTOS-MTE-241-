#include "rtx.h"
#include "primitives.h"

int send_message (char dst_process_id,Msg_Env *msg_envelope);
Msg_Env* receive_message();
int get_console_chars(Msg_Env *message_envelope);
int send_console_chars(Msg_Env *message_envelope);
Msg_Env* request_msg_env();
int release_msg_env (Msg_Env *message_envelope);
int request_process_status (Msg_Env *message_envelope);
int terminate();
int change_priority(int new_priority, int target_process_id);
int request_delay(char time_delay, char wakeup_code, Msg_Env* message_envelope);
int get_trace_buffers(Msg_Env* message_envelope);
int release_processor();
