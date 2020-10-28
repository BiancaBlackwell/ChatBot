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
#define PORT 22110

//almost exactly like input, basically just run at all times!
void init_receiver(void* unused){
	pthread_create(&receiverThread, NULL, receiver, NULL);
}
void* receiver(void* unused){
    char buffer[MSG_MAX_LEN] = {0};
	printf("Starting up Receiver Module...\n");
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        printf("Receiver Socket Failed :( \n");
        exit(1);
    }
    //Address
    struct sockaddr_in myAddress;
    memset(&myAddress, 0, sizeof(myAddress));
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = htons(INADDR_ANY); //my address to receieve
    myAddress.sin_port = htons(22211); //my port to recieve [HARDCODED RN, FIX THAT]

    //Create UDP socket
    int n = bind(sockfd, (struct sockaddr*) &myAddress, sizeof(myAddress));
    if(n == -1){
        printf("Failed to bind receiver socket\n");
        close(sockfd);
        exit(1);
    }

    int h;
    while(true){
        //get data (blocking)
        //change address sent to client

        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MSG_MAX_LEN];
        int h = recvfrom(sockfd, messageRx, MSG_MAX_LEN, MSG_WAITALL, 0, &sin_len); //we do absolutely no verification on this of who sent the packet!
        messageRx[h] = '\n';
        //do something with the message
        printf("MESSAGE RECEIEVED! %s\n", messageRx);
    }
    printf("Done rx thread!");
    close(sockfd);
}
void close_receiver(void* unused){
	printf("Shutting down Receiver Module...\n");
	pthread_cancel(receiverThread);
	pthread_join(receiverThread, NULL);	
}