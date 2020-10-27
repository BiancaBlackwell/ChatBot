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

static pthread_t senderThread;
extern struct List_s *outgoing;

void init_sender(void* unused){
	pthread_create(&senderThread, NULL, sender, NULL);
}
void* sender(void* unused){
	printf("Starting up Sender Module...\n");
	//wait for list to be non-empty
	while(true){
		if(List_count(outgoing) != 0){
			int sockfd; 
		    char buffer[MSG_MAX_LEN]; 
		    char *hello = "Hello from client"; 
		    struct sockaddr_in     servaddr; 
		  
		    // Creating socket file descriptor 
		    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		        perror("socket creation failed"); 
		        exit(EXIT_FAILURE); 
		    } 
		  
		    memset(&servaddr, 0, sizeof(servaddr)); 
		      
		    // Filling server information 
		    servaddr.sin_family = AF_INET; 
		    servaddr.sin_port = htons(PORT); 
		    servaddr.sin_addr.s_addr = INADDR_ANY; 
		      
		    int n, len; 
		      
		    sendto(sockfd, (const char *)hello, strlen(hello), 
		        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
		            sizeof(servaddr)); 

		    printf("Hello message sent.\n"); 
		          
		    n = recvfrom(sockfd, (char *)buffer, MSG_MAX_LEN,  
		                MSG_WAITALL, (struct sockaddr *) &servaddr, 
		                &len); 
		    buffer[n] = '\0'; 
		    printf("Server : %s\n", buffer); 
		  
		    close(sockfd); 
		}
	}
	//when non-empty, list_remove() and send that message!
}
void close_sender(void* unused){
		printf("Shutting down Sender Module...\n");
		pthread_cancel(senderThread);
		pthread_join(senderThread, NULL);
}