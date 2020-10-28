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

static pthread_t receiverThread;
struct List_s *incoming;
//almost exactly like input, basically just run at all times!
void init_receiver(void* unused){
	pthread_create(&receiverThread, NULL, receiver, NULL);
}
void* receiver(void* unused){
	printf("Starting up Receiver Module...\n");
    char buffer[MSG_MAX_LEN]; 
    char *message = "Hello Client"; 
    int listenfd, len; 
    struct sockaddr_in servaddr, cliaddr; 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // Create a UDP Socket 
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET;  
   
    // bind server address to socket descriptor 
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
    while(true){
        //receive the datagram 
        len = sizeof(cliaddr); 
        int n = recvfrom(listenfd, buffer, sizeof(buffer), 
                0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
        buffer[n] = '\0'; 
        puts(buffer); 
        printf("YOU HAVE MAIL!\n");
    }

}
void close_receiver(void* unused){
	printf("Shutting down Receiver Module...\n");
	pthread_cancel(receiverThread);
	pthread_join(receiverThread, NULL);	
}