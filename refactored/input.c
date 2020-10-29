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
	
	char* message;
	//use a malloc call to grab blocks of memory assigned to a pointer that i will the shoving in the list
	//only ever having one pointer! but, it's being moved addresses to talk about different chunks
	//saving the addresses of these pointers by shoving them into the list
	//free memory after things are getting taken off the list

	outgoing = List_create(); //for messages that are to be sent

	while(true){
		//malloc a new chunk of memory for new message
		message = malloc(MSG_MAX_LEN*sizeof(char));
		//load it up with 0's to be safe
		if (message != NULL){
    		memset(message, 0, MSG_MAX_LEN*sizeof(char));
		}
		else{
			printf("Oh no! malloc error in input.c\n");
			exit(1);
		}
		//Listen for user input
		if(fgets(message, MSG_MAX_LEN, stdin) !=  NULL){
			pthread_mutex_lock(&outgoingMutex);
			List_add(outgoing,message);	//critical section
			pthread_mutex_unlock(&outgoingMutex);
			pthread_cond_signal(&senderSignal);
		}

	}
}

void close_input(void* unused){
	printf("Shutting Down Input Module...\n");
	pthread_cancel(inputThread);
	pthread_join(inputThread, NULL);
}

