//#include "queues.c"

#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "testing functions.h"
int main()
{
	

	
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
	printf("now attempting to enter dequeue_selected_pcb\n");
	char p_id = 4;
	pcb2=dequeue_selected_pcb(queue1,p_id);
	printf("now reprinting queue with pid = %i removed\n",p_id);
	print_pcb_queue(queue1);
	
	printf("now printing queue2 with pid = %d as only element\n",p_id);
	print_pcb(pcb2)	;
	
	pcb_queue *queue2;
	queue2 = (pcb_queue*)malloc(sizeof(pcb_queue));
	initialize_queue(queue2);
	enqueue(queue2, pcb2);
	print_pcb_queue(queue2);
	pcb2=dequeue_selected_pcb(queue2, p_id);
	print_pcb_queue(queue2);
	printf("now reprinting queue with pid = %i removed\n",p_id);
	print_pcb_queue(queue1);
	
	
	/*printf("now reprinting queue with pid = %d removed\n",p_id);*/
	
	
	//testing pcb pointer
	pcb *pcb3;
	printf("the queue currently is:\n");
	print_pcb_queue(queue1);
	p_id=5;
	pcb3 = pcb_pointer(queue1,p_id);
	printf("the queue now is:\n");				
	print_pcb_queue(queue1);
	printf("PCB3 is:\n");
	print_pcb(pcb3);
	

	
	
	
	
	
	
	printf("enter any key to exit\n");
	
	getchar();
    return 1;
}