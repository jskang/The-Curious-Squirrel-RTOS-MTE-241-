/* Include Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/* Define constants*/
#define BUFFERSIZE 129
#define MAXCHAR 80

/* Define structures */
typedef struct{
  int ok_flag;
	char input_data[MAXCHAR];
	int length;
} uart_buffer;

/** Do we need more things? **/