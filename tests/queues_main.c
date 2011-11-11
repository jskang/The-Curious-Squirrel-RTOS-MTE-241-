//#include "queues.c"

#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "testing functions.h"
int main()
{
	

	/*
	pcb_queue *queue1;
	queue1 = (pcb_queue*)malloc(sizeof(pcb_queue));
	
	pcb *pcb1, *pcb2;
	pcb1 = (pcb*)malloc(sizeof(struct pcb));
	int i;
	
	
	initialize_queue(queue1);
	if (queue1->head== NULL)
		printf("queue1 head points to null \n");
	if (queue1->tail== NULL)
		printf("queue1 tail points to null \n");

	
	if (empty_pcb_queue(queue1))
		printf("queue1 is empty\n");
	
	if(enqueue(queue1,pcb1)==1);
		printf("successfully added\n");
	
	if (empty_pcb_queue(queue1)==1)
		printf("queue1 is empty\n");
	if(pcb1 == NULL)
		printf("uh oh");
	if(queue1->head == pcb1)
		printf("queue1->head == pcb1");
	
	//testing enqueue
	for (i=0; i<10; i++) {
		pcb2 = (pcb*)malloc(sizeof(struct pcb));
		pcb2->pid = i;
		pcb2->state=i;
		pcb2->priority=i;
		enqueue(queue1,pcb2);
		pcb2=NULL;
		if(enqueue(queue1,pcb2) == INVALID_PCB_POINTER)
			printf("pcb --> null was not added\n");
			
	}
	pcb1->pid=1;
	pcb1->state=1;
	pcb1->priority=2;
	print_pcb_queue(queue1);
	
	
	//testing dequeue
	printf("now 3 processes will be dequeued\n");
	for(i=0;i<3; i++){
		pcb2=dequeue(queue1);
		print_pcb(pcb2);
	}
	printf("will now reprint queue\n");
	print_pcb_queue(queue1);
	
	
	
	// testing dequeue_selected_pcb
	
	pcb_queue *pcb_queue3,*pcb_queue4;
	pcb_queue3 = (pcb_queue*)malloc(sizeof(pcb_queue));
	pcb_queue4 = (pcb_queue*)malloc(sizeof(pcb_queue));
	
	pcb *pcb3;
	initialize_queue(pcb_queue3);
	initialize_queue(pcb_queue4);
	for(i=0; i<50; i++){
			pcb3 = (pcb*)malloc(sizeof(struct pcb));
			pcb3->pid = i;
			pcb3->state=i;
			pcb3->priority=i;
		if(enqueue(pcb_queue3,pcb3) == 1)
			printf("PCB %i successfully added\n",i);
	}
		
	char to_remove=9;
	
	for (to_remove=0; to_remove<50; to_remove+=2)
	{
		pcb3 = dequeue_selected_pcb(pcb_queue3,to_remove);
		printf("-------------------------------\n");
		printf("\nnow removing pcb with pid= %i\n",to_remove);
		print_pcb(pcb3);
		printf("-------------------------------\n");
		printf("enqueue removed pcb to pcb_queue4");
		enqueue(pcb_queue4,pcb3);
	}

	printf("-------------------------------\n");
	printf("\n\n now the pcb_queue3 looks like\n\n");
	print_pcb_queue(pcb_queue3);
	printf("-------------------------------\n");
	printf("\n\n now the pcb_queue4 looks like\n\n");
	print_pcb_queue(pcb_queue4);
	
	printf("now adding back to pcb_queue3\n");
	for (to_remove=0; to_remove<50; to_remove+=2)
	{
		pcb3 = dequeue_selected_pcb(pcb_queue4,to_remove);
		enqueue(pcb_queue3,pcb3);
	}
	printf("-------------------------------\n");
	printf("\n\n now the pcb_queue3 looks like\n\n");
	print_pcb_queue(pcb_queue3);
	printf("-------------------------------\n");
	printf("\n\n now the pcb_queue4 looks like\n\n");
	print_pcb_queue(pcb_queue4);
		
	//testing pcb pointer
	pcb *pcb3;
	printf("the queue currently is:\n");
	print_pcb_queue(queue1);
	p_id=5;
	pcb3 = pcb_pointer(queue1,p_id);
	printf("the queue now is:\n");				
	print_pcb_queue(queue1);
	printf("PCB3 is:\n");
	print_pcb(pcb3);*/
	
	/*printf("---------------Now testing Message Envelopes Queues------------------/n/n");
	msg_queue *m_queue1;
	m_queue1 = (msg_queue*)malloc(sizeof(msg_queue));
	
	Msg_Env *msg1, *msg2;
	msg1 = (Msg_Env*)malloc(sizeof(struct Msg_Env));
	
	
	initialize_msg_queue(m_queue1);
	if (m_queue1->head== NULL)
		printf("m_queue1 head points to null \n");
	if (m_queue1->tail== NULL)
		printf("m_queue1 tail points to null \n");
	
	
	if (empty_msg_queue(m_queue1))
		printf("queue1 is empty\n");
	
	if(msg_enqueue(m_queue1,msg1)==1);
	printf("successfully added\n");
	
	if (empty_msg_queue(m_queue1)==1)
		printf("queue1 is empty\n");
	else
		printf("m_queue1 is not empty\n");
	
	if(msg1 == NULL)
		printf("uh oh\n");
	if(m_queue1->head == msg1)
		printf("queue1->head == msg1\n");
	
	//testing enqueue more thoroughly
	for (i=0; i<10; i++) {
		msg2 = (Msg_Env*)malloc(sizeof(struct Msg_Env));
		msg2->owner_id=i;
		msg2->sender_id=0;
		msg2->time_stamp=0;
		msg2->message_type=0;
		msg2->flag=0;
		msg_enqueue(m_queue1,msg2);
		msg2=NULL;
		if(enqueue(queue1,pcb2) == INVALID_PCB_POINTER)
			printf("pcb --> null was not added\n");
		
	}
	print_msg_queue(m_queue1);

	//testing dequeue
	printf("now 3 message envelopes will be dequeued\n");
	for(i=0;i<3; i++){
		msg2=msg_dequeue(m_queue1);
		print_msg(msg2);
	}
	printf("-------------------------------\n");
	printf("will now reprint m_queue1\n");
	print_msg_queue(m_queue1);*/

	
/*	
	
	//here the testing for ready process queue will start
	
	pcb_queue *rpq_queue[4];
	pcb_queue *rpq_queue1[4];
	//rpq_queue = (pcb_queue**)malloc(4*sizeof(pcb_queue*));
	
	pcb *pcb7, *pcb8;
	
	initialize_rpq_queue(rpq_queue);
	initialize_rpq_queue(rpq_queue1);
	print_rpq_test(rpq_queue);
	

	for(i=0; i<50; i++){
		pcb7 = (pcb*)malloc(sizeof(struct pcb));
		pcb7->pid = i;
		pcb7->state = READY;
		pcb7->priority=(i%4);
		printf("----------------------------------------\n");
		printf("enqueueing process with priority=%i\n",pcb7->priority);
		test_rpq_enqueue(rpq_queue,pcb7);
		
	}
	printf("now printing the entire rpq\n");
		print_rpq_test(rpq_queue);
	printf("---------------------------------------------------\n");
	printf("now items will be dequeued and added to a new queue\n");
	for(i=0;i<30;i++){
		pcb7=test_rpq_dequeue(rpq_queue);
		test_rpq_enqueue(rpq_queue1,pcb7);
		printf("dequeued pcb with priorit=%i\n",pcb7->priority);
		
	}
	printf("rpq_queue now looks like\n");
	print_rpq_test(rpq_queue);
	printf("\n\n\n");
	printf("rpq_queue1 looks like\n");
	print_rpq_test(rpq_queue1);*/
	
	
		printf("enter any key to exit\n");
	
	getchar();
    return 1;
}