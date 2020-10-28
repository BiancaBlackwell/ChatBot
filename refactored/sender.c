#include "input.h"
#include "sender.h"

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

pthread_t senderThread;
extern struct List_s *outgoing;
extern pthread_mutex_t outgoingMutex;
extern pthread_cond_t senderSignal;

void init_sender(void* unused){
	pthread_create(&senderThread, NULL, sender, NULL);
}
void* sender(void* unused){
	printf("Starting up Sender Module...\n");
	//wait for list to be non-empty
			int sockfd; 
		    char buffer[MSG_MAX_LEN]; 
		    struct sockaddr_in friendAddress; //declare struct for friend's address
		  
		    // Creating socket file descriptor 
		    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { //should the protocol actually be 0?
		        printf("socket creation failed in Sender Module\n"); 
		        exit(1); //add in better exit handling then this >:(
		    } 
		  
		    memset(&friendAddress, 0, sizeof(friendAddress)); //making sure our memory is clear and not whatevery garboly goop was there before
		      
		    // Populate struct for friend's address!!
		    friendAddress.sin_family = AF_INET;
		    friendAddress.sin_port = htons(PORT); //myPort so my friend knows where I am 
		    friendAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY will work if both people are on the same machine...(?) TODO : improve for multi-machine 
		      
		    int n, len; 

	while(true){ 
			pthread_mutex_lock(&outgoingMutex);{
			pthread_cond_wait(&senderSignal,&outgoingMutex);
			if(List_count(outgoing) > 0){
				List_first(outgoing);
				char *message = List_remove(outgoing); //todo: change this to the message form the list
				printf("Removed from outgoing list: %s", message);
				//when there is a message to be sent... send it! otherwise... hang around and do nothing. 
				//if ever you see a "!" ...blow up
			 	sendto(sockfd, (const char *)message, strlen(message), 
			        MSG_CONFIRM, (const struct sockaddr *) &friendAddress,  
			            sizeof(friendAddress)); 

			    printf("Your message was sent.\n"); 
			          
			    /**n = recvfrom(sockfd, (char *)buffer, MSG_MAX_LEN,  
			                MSG_WAITALL, (struct sockaddr *) &friendAddress, 
			                &len); 
			    buffer[n] = '\0'; 
			    printf("Server : %s\n", buffer); **/
			}
			pthread_mutex_unlock(&outgoingMutex);
		}
	}
	close(sockfd); 
}
void close_sender(void* unused){
		printf("Shutting down Sender Module...\n");
		pthread_cancel(senderThread);
		pthread_join(senderThread, NULL);
}