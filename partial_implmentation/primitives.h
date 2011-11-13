#include "rtx.h"

int k_send_message (char dest_process_id, Msg_Env *msg_envelope);
Msg_Env* k_receive_message(void);
int k_get_console_chars(Msg_Env *message_envelope);
int k_send_console_chars(Msg_Env *message_envelope);
