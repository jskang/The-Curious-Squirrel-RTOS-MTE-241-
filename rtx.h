/*************************************************************************************************************
Filename: rtx.h
Author: Bhavik Vyas, JinSung Kang
Revision: 1.1
Comments: Global variables and struct definitions for Initialization
*************************************************************************************************************/
#ifndef _GLOBAL_VARIABLE_
#define _GLOBAL_VARIABLE_

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <setjmp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

/* Decalare global constants*/
// Message Types
#define M_TYPE_EMPTY 0
#define M_TYPE_DEFAULT 1
#define M_TYPE_DISPLAY_BACK 2
#define M_TYPE_CONSOLE_INPUT 3
#define M_TYPE_MESSAGE_TRACE 4
#define M_TYPE_REQ_PROCESS_STATUS 5
#define M_TYPE_MSG_DELAY 6
#define M_TYPE_MSG_DELAY_BACK 7
#define M_TYPE_WALL_CLOCK 8
#define M_TYPE_WALL_CLOCK_SET 9
#define M_TYPE_MSG_ACK 10

// Global variables
#define N_TOTAL_PCB 9
#define N_MSG_ENV 30
#define N_I_MSG_ENV 30
#define MESSAGE_SIZE 129

// Process IDs
#define PID_PROCESS_A 0
#define PID_PROCESS_B 1
#define PID_PROCESS_C 2
#define PID_PROCESS_CCI 3
#define PID_PROCESS_NULL 4
#define PID_PROCESS_CLOCK 5
#define PID_I_PROCESS_CRT 6
#define PID_I_PROCESS_KBD 7
#define PID_I_PROCESS_TIMER 8

// Process States
#define READY 0
#define RUNNING 1
#define BLOCKED_ON_RESOURCE 2
#define BLOCKED_ON_RECEIVE 3
#define INTERRUPTED 4
#define SLEEP 5
#define NO_BLK_RCV 6 //state needed for partial implimentation, not used for actual project

// Error Codes
#define DESTINATION_PID_ERROR -100
#define INVALID_MESSAGE_PTR_ERROR -101
#define INVALID_PRIORITY_ERROR -102
#define INVALID_PID_ERROR -103
#define INVALID_PARMETER_REQ_DELAY_ERROR -104
#define INVALID_PCB_POINTER -105
#define INVALID_MSG_POINTER -106
#define INVALID_MESSAGE_DELETE -107
#define INVALID_PCB_STATE_ERROR -108
#define INVALID_QUEUE_ERROR -109

// booleans
#define OFF 0
#define ON 1
#define FALSE 0
#define TRUE 1

/* Struct Definitions */
typedef struct msg_trace{
     char sender_PID;
     char receiver_PID;
     char time_stamp;
     char m_type;
}msg_trace;

// PCB Struct
typedef struct pcb{
	 struct pcb *next;            
     struct pcb *pcb_all;            
     char pid;
     char state;            
     char priority;            
     struct msg_queue *inbox;        
     jmp_buf jbdata;
}pcb;

//pcb queue struct definition
typedef struct pcb_queue{
     pcb *head;
     pcb *tail;
     int n_elements;
}pcb_queue;


// Message Envelope Struct
typedef struct Msg_Env{
     struct Msg_Env *env_all;
     struct Msg_Env *next;
     unsigned int owner_id;
     unsigned int sender_id;
     int time_stamp;
     char message_type;
     char flag;
     char message[MESSAGE_SIZE];
     int size;
}Msg_Env;

//msg queue struct definition
typedef struct msg_queue{
	Msg_Env *head;
	Msg_Env *tail;
	char n_elements;
}msg_queue;


// Global Message Trace

extern pcb *current_process; //global variables
extern pcb_queue *all_pcbs_queue;
extern pcb_queue *blocked_on_resource_queue;
extern pcb_queue *blocked_on_receive_queue;
extern pcb_queue *interrupted_queue;
extern pcb_queue *sleep_queue;
extern pcb_queue *priority_ready_queue[4];  
extern pcb_queue *all_pcbs;
extern pcb_queue *blocked_message_envelope;
extern pcb_queue *blocked_receive;
extern msg_queue *all_envelopes;
extern msg_queue *free_envelopes;
extern msg_queue *free_i_envelopes;
#endif





