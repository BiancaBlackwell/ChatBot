//The following are modules for each pthread
//#include "receiver.h" 
//#include "sender.h"
//#include "screen.h"
#include "input.h"

#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MSG_MAX_LEN 1024
#define PORT 22110

static int socketDescriptor;
//make pthreads for each module global so there's no issues there
//remember to lock access to shared list whenever someone is using it

int main(int argCount, char** args){

	init_input(NULL);

	sleep(10);

	close_input(NULL);


	printf("We did it reddit!");


	return 0;
}