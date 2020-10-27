#include "input.h"
#include "sender.h"

#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


static pthread_t inputThread;
struct List_s *outgoing;

void init_input(void* unused){
	//todo: make this pass a shared mutex variable to lock list access
	pthread_create(&inputThread, NULL, listener, NULL);
}

void new_input(char *message, List* outgoing){
	if(message[0] == '!'){
		printf("Shutting Down Input Module...");
		fflush(stdout);
		return close_input(NULL);
	}
	List_add(outgoing,message);
	//char* currentmessage = List_remove(outgoing);

	//todo: instead of printing, have it add to a list
	//printf("%s \n", currentmessage);
}

void* listener(void* unused){
	printf("Starting up Input Module...\n");
	//possible issue writing over message if i make a new message before it is sent?
	char message[MSG_MAX_LEN];
	outgoing = List_create(); //for messages that are to be sent
	
	while(true){
		if(scanf("%s", message) != 0){
			new_input(message, outgoing);
		}
	}
}

void close_input(void* unused){
		pthread_cancel(inputThread);
		pthread_join(inputThread, NULL);
}

