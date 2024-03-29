#include "input.h"
#include "sender.h"
#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <arpa/inet.h>  
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

//The Following is the code for my Sender Module for CMPT 300 A2

pthread_t senderThread;
extern struct List_s *outgoing;
extern pthread_mutex_t outgoingMutex;
extern pthread_cond_t senderSignal;

extern char* mPORT;
extern char* fAddr;
extern char* fPORT;

struct addrinfo* result;
int error;

void init_sender(void* unused){
	pthread_create(&senderThread, NULL, sender, NULL);
}
void* sender(void* unused){
	printf("Starting Sender Module...\n");
	//wait for list to be non-empty
		int sockfd; 
	    char buffer[MSG_MAX_LEN]; 
	    struct sockaddr_in friendAddress; //declare struct for friend's address
	    int n;
	    int len;
	  
	    // Creating socket file descriptor 
	    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	    if(sockfd == -1){
	    	printf("Sender Socket failed :( \n");
	    	exit(1);
	    }
		    
	memset(&friendAddress, 0, sizeof(friendAddress)); //making sure our memory is clear and not whatevery garboly goop was there before

	error = getaddrinfo(fAddr, fPORT,NULL,&result);
	if(error != 0){
		printf("Oh no! Address issue in sender.c\n");
		exit(1);
	}

	// Populate struct for friend's address!!
    friendAddress.sin_family = AF_INET;
    friendAddress.sin_port = htons(atoi(fPORT));	//passed a char* myPort, convert string to short...
    friendAddress.sin_addr.s_addr = INADDR_ANY; // csil-cpu-1 getaddrinfo (check assginment descrip, man pages) [will use domain name w. port to find other machine]
    printf("Okay! we are going to be sending to %s, on port %s\n", fAddr, fPORT);

	while(true){ 
			pthread_mutex_lock(&outgoingMutex);{
			pthread_cond_wait(&senderSignal,&outgoingMutex);
			//Critical section! (hence locked)
			if(List_count(outgoing) > 0){
				List_first(outgoing);
				//here i don't need to malloc, send out whats at the memory address
				char *message = List_remove(outgoing);

				//when there is a message to be sent... send it! otherwise... hang around and do nothing. 
				//if ever you see a "!" ...blow up
				//len is a return code handler to make sure we didn't fail to send
			 	len = sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *) &friendAddress, sizeof(friendAddress)); 
			 	if(len == -1){
			 		printf("Message failed to send \n");

			 	}
			 	if(message[0] == '!'){ 
					printf("Okay, shutting down...\n");
					exit(1);
				}
			 	//free the memory at the pointer before mentally throwing it out entirely
			 	free(message);
			}
			pthread_mutex_unlock(&outgoingMutex);
		}
	}
	close(sockfd); 
}
void close_sender(void* unused){
	//super fool-proof murder the thread
	printf("Shutting down Sender Module...\n");
	pthread_cancel(senderThread);
	pthread_join(senderThread, NULL);
}