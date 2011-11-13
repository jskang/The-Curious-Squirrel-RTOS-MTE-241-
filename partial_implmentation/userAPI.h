#include "rtx.h"
#include "primitives.h"

int send_message (char dst_process_id,Msg_Env *msg_envelope);
Msg_Env* receive_message();
int get_console_chars(Msg_Env *message_envelope);
int send_console_chars(Msg_Env *message_envelope);
