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
pthread_mutex_t incomingMutex = PTHREAD_MUTEX_INITIALIZER;
char* mPORT;
char* fAddr;
char* fPORT;

//pthread_mutex_t outgoinglock;
//make pthreads for each module global so there's no issues there
//remember to lock access to shared list whenever someone is using it

int main(int argCount, char** args){
	if(argCount >= 3){
		mPORT = args[1]; //my Port 
		fAddr = args[2];
		fPORT = args[3];
	}
	else{
		printf("Not Enough Info. Please Run as ./chatbot [myPort] [friends address] [friend's port]\n");
		exit(1);
	}

	init_input(NULL); // (char* myPort?)
	init_receiver(NULL); // needs port that this instance will be getting messages in
	init_sender(NULL); // needs port of friend and address string to lookup in getaddrinfo()
	init_screen(NULL);

	sleep(100);

	close_receiver(NULL);
	close_input(NULL);
	close_sender(NULL);
	close_screen(NULL);


	printf("Program Finished Naturally\n");


	return 0;
}