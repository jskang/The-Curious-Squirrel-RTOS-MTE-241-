//#include "queues.c"
#include "rtx.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pcb *test;
	pcb *test1;
	pcb *head;

	test = (pcb*) malloc(sizeof(pcb));
	test1 = (pcb*) malloc(sizeof(pcb));
	
	head = test;

	test->priority = 1;
	test->pid = 1;
	test->next=test1;
	test1->priority = 1;
	test1->pid = 5;
	
	if (head->next->pid == 5)
		printf ("hellO \n");
	if (head->pid == 1)
		printf ("Fuck yeah \n");
	return 0;
}
