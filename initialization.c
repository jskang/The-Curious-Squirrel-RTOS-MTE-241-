#include <stdio.h>
#include <stdlib.h>
#include "rtx.h"

typedef struct initialization_table{
  char pid;
	char state;
	char priority;
}initialization_table;

initialization_table i_table[N_TOTAL_PCB][3];

int initialization(){
	
	// Process P only required for partial implementation.
	i_table[0].pid = PID_PROCESS_P;
	i_table[0].state = NO_BLK_RCV;
	i_table[0].priority = 0;
	
	i_table[1].pid = PID_I_PROCESS_CRT;
	i_table[1].state = I_PROCESS;
	i_table[1].priority = 0;
	
	i_table[2].pid = PID_I_PROCESS_KBD;
	i_table[2].state = I_PROCESS;
	i_table[2].priority = 0;
	
	i_table[3].pid = PID_I_PROCESS_TIMER;
	i_table[3].state = I_PROCESS;
	i_table[3].priority = 0;

	i_table[4].pid = PID_PROCESS_A;
	i_table[4].state = READY;
	i_table[4].priority = 0;

	i_table[5].pid = PID_PROCESS_B;
	i_table[5].state = READY;
	i_table[5].priority = 0;

	i_table[6].pid = PID_PROCESS_C;
	i_table[6].state = READY;
	i_table[6].priority = 0;

	i_table[7].pid = PID_PROCESS_CLOCK;
	i_table[7].state = READY;
	i_table[7].priority = 0;

	i_table[8].pid = PID_PROCESS_CCI;
	i_table[8].state = READY;
	i_table[8].priority = 0;

	i_table[9].pid = PID_PROCESS_NULL;
	i_table[9].state = READY;
	i_table[9].priority = 4;
	
	// Initialize PCBs
	int i;
	tempNumProcess = 3; // Temporary number of processes for partial implementation.
	pcb* pcbList[tempNumProcess];
	for(i = 0;i<tempNumProcess;i++){
		pcbList[i] = (pcb*)(malloc(sizeof(pcb)));
		pcbList[i]->inbox = (msg_queue*)(malloc(sizeof(msg_queue)));
		if(pcbList[i] == NULL){
			return INVALID_QUEUE_ERROR;
		}		
		pcbList[i]->pid = i_table[i].pid;
		pcbList[i]->state = i_table[i].state;
		pcbList[i]->priority = i_table[i].priority;
		pcbList[i]->next = NULL;
		pcbList[i]->inbox->head = NULL;
		pcbList[i]->inbox->tail = NULL;
	}
	
	Msg_Env* tempMsgEnv;
	for(i = 0;i<N_MSG_ENV;i++){
		tempMsg = (Msg_Env*)malloc(sizeof(Msg_Env));
		if(tempMsg == NULL){
			return INVALID_MSG_POINTER;
		}
		msg_enqueue_all(tempMsgEnv);
		msg_enqueue(free_envelopes,tempMsgEnv);
	}
	
	for(i = 0;i<N_I_MSG_ENV;i++){
		tempMsg = (Msg_Env*)malloc(sizeof(Msg_Env));
		if(tempMsg == NULL){
			return INVALID_MSG_POINTER;
		}
		msg_enqueue(all_i_envelopes,tempMsg);
		msg_enqueue(free_i_envelopes,tempMsg);
	}
	
}
