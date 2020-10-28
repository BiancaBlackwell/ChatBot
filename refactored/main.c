//The following are modules for each pthread
#include "receiver.h" 
#include "sender.h"
#include "screen.h"
#include "input.h"

#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MSG_MAX_LEN 1024
#define PORT 22110

struct List_s *outgoing;
pthread_mutex_t outgoingMutex = PTHREAD_MUTEX_INITIALIZER;

//pthread_mutex_t outgoinglock;
//make pthreads for each module global so there's no issues there
//remember to lock access to shared list whenever someone is using it

int main(int argCount, char** args){

	init_input(NULL);
	init_receiver(NULL);
	init_sender(NULL);
	init_screen(NULL);

	sleep(100);

	close_receiver(NULL);
	close_input(NULL);
	close_sender(NULL);
	close_screen(NULL);


	printf("Program Finished Naturally\n");


	return 0;
}