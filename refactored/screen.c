#include "input.h"
#include "sender.h"
#include "screen.h"
#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

static pthread_t displayThread;
extern struct List_s *incoming;
extern pthread_mutex_t incomingMutex;
extern pthread_cond_t screenSignal;
struct addrinfo* result;

void init_screen(void* unused){
	pthread_create(&displayThread, NULL, display, NULL);
}
void* display(void* unused){
	printf("Starting Screen Module...\n");
	
	while(true){
		pthread_mutex_lock(&incomingMutex);
		pthread_cond_wait(&screenSignal,&incomingMutex);
		if(List_count(incoming) > 0){
			List_first(incoming);
			char* messageRx = List_remove(incoming);
			printf("Friend: %s", messageRx);
			fflush(stdout);
			//load it up with whatever is in the first position of incoming
			//print it out on stdout
			if(messageRx[0] == '!'){
				printf("Okay, shutting down...\n");
				exit(1);
			}
			//free the memory at the pointer address
			free(messageRx);
		}
		pthread_mutex_unlock(&incomingMutex);

	}
}
void close_screen(void* unused){
	printf("Shutting down Screen Module...\n");
	pthread_cancel(displayThread);
	pthread_join(displayThread, NULL);	
}