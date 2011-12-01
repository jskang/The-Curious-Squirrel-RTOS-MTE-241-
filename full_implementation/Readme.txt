The partial implementation for this Real Time Operating System is intended for the purpose of MTE 241.
This project was created by:
	Bhavik Vyas - 20305110
	JinSung Kang - 20314830
	Markus Trapp - 20351628
	Milan Stanivuk - 20341751
	Group - 17

The content of the source files are as follows:

init.c - This file initializes the RTX which include the initalization of PCBs, message envelopes, forks keyboard and crt processes.
kernel.c - Calls initialization and contains the global variables. The program starts from this file.
atomic.c - This file contains the logic for the atomic function.
queues.c - This file contains the functionalities to mainpulate queues.
keyboard.c - This file contains the code to run the keyboard u-process.
crt.c - This file contains the code to run the crt u-process.
userProcesses.c - This file handles the functionality user processes A, B, C, and the CCI and Wall Clock processes.
primitives.c - This file handles the funtionality for the kernel primitives. The functions are: k_send_message, k_receive_message, k_get_console_chars, k_send_console_chars, k_request_msg_env, k_release_msg_env, k_request_process_status, k_terminate, k_change_priority, k_request_delay, k_get_trace_buffers, k_release_processor, process_switch, context_switch.
userAPI.c - This fie contains the user version of the primitives.
iproc.c - This file contains the functionality of the i-processes that are required in the RTX. The processes are: crt i-process, keyboard i-process, and timer i-process.


The content of the header files are as follows: 

init.h - This is the header for init.c
rtx.h - This is the header file that contains the global variables for the RTX and contains the structs required such as the PCBS, message envelopes, queues, etc.
atomic.h - This is the header for atomic.c
queues.h - This is the header for queues.c
kbcrt.h - This is the header for the keyboard.c and header.c. It contains the structure for the buffer.
userProcesses.h - This is the header for the userProcesses.c
primitives.h - This is the header for primitives.c
userAPI.h - This is the header for the userAPI.c
iproc.h - This is the header for iproc.c .

There is also an additional file named "makefile" which compiles and links all the source and object files together.

The project can be compiled using the 'make clean' and 'make all' commands. To test the program do the following:
make clean
make all
./RTX-G17

PLEASE NOTE: As of right now the RTOS works on Ubuntu but does not work on ECE linux. The group has spoken to the Professor about this and the professor has agreed that we may submit the current working version we have (which works on Ubuntu) and may resubmit another version that also works on ECE linux before the demo without being penalized for a late submission. Thank you.
