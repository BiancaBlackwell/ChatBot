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
	printf("WELCOME TO S-TALK BY BIANCA BLACKWELL 301 304 375 for CMPT 300 A2\n");
	if(argCount >= 3){
		mPORT = args[1]; //my Port 
		fAddr = args[2];
		fPORT = args[3];
	}
	else{
		printf("Not Enough Info. Please Run as ./s-talk [myPort] [friends address] [friend's port]\n");
		exit(1);
	}

	//strange interactions occured when passing arguments directly, so I found a way to not do that
	init_input(NULL); 
	init_receiver(NULL); 
	init_sender(NULL); 
	init_screen(NULL);

	//my code will time out after ~166 minutes, but this was intentional as a safety measure (incase it was left running on csil)
	sleep(10000);

	close_receiver(NULL);
	close_input(NULL);
	close_sender(NULL);
	close_screen(NULL);


	printf("s-talk has Timed Out!\n");


	return 0;
}