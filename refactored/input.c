#include "input.h"
#include "sender.h"

#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


static pthread_t inputThread;

extern struct List_s *outgoing;
extern pthread_mutex_t outgoingMutex;
pthread_cond_t senderSignal = PTHREAD_COND_INITIALIZER;

void init_input(void* unused){
	pthread_create(&inputThread, NULL, listener, NULL);
}

void* listener(void* unused){
	printf("Starting up Input Module...\n");
	
	char message[MSG_MAX_LEN];
	outgoing = List_create(); //for messages that are to be sent

	while(true){
		if(fgets(message, MSG_MAX_LEN, stdin) !=  NULL){
			pthread_mutex_lock(&outgoingMutex);
			printf("Adding to outgoing list: %s", message);
			List_add(outgoing,message);
			pthread_mutex_unlock(&outgoingMutex);
			pthread_cond_signal(&senderSignal);
		}

	}
}

void close_input(void* unused){
	printf("Shutting Down Input Module...");
	pthread_cancel(inputThread);
	pthread_join(inputThread, NULL);
}

