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
extern pthread_mutex_t incomingMutex;
pthread_cond_t screenSignal = PTHREAD_COND_INITIALIZER;

extern char* mPORT;
extern char* fAddr;
extern char* fPORT;

void init_receiver(void* unused){
	pthread_create(&receiverThread, NULL, receiver, NULL);
}
void* receiver(void* unused){
	printf("Starting up Receiver Module...\n");
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        printf("Receiver Socket Failed :( \n");
        exit(1);
    }
    
    struct sockaddr_in myAddress;
    memset(&myAddress, 0, sizeof(myAddress));
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = htons(INADDR_ANY); //my address to receieve
    myAddress.sin_port = htons(atoi(mPORT)); //my port to recieve

    //Bind the UDP socket!
    int n = bind(sockfd, (struct sockaddr*) &myAddress, sizeof(myAddress));
    if(n == -1){
        printf("Failed to bind receiver socket\n");
        close(sockfd);
        exit(1);
    }

    incoming = List_create();
    char *messageRx;
    int h;
    printf("Okay! We are going to be listening sent to port %s\n", mPORT);
    while(true){
        //malloc a pointer for getting a nice new memory chunk and make sure it's clear
        messageRx = malloc(MSG_MAX_LEN*sizeof(char));
        if(messageRx != NULL){
            memset(&messageRx[0], 0, sizeof(messageRx));
        }
        else{
            printf("Oh no! malloc failed in receiver.c\n");
            exit(1);
        }
    
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);

        int h = recvfrom(sockfd, messageRx, MSG_MAX_LEN, MSG_WAITALL, 0, &sin_len); //we do absolutely no verification on this of who sent the packet! NOM THE UDP PACKET

        pthread_mutex_lock(&incomingMutex);

        List_add(incoming,messageRx);
        pthread_mutex_unlock(&incomingMutex);
        pthread_cond_signal(&screenSignal);

    }
    printf("Done rx thread!");
    close(sockfd);
}
void close_receiver(void* unused){
	printf("Shutting down Receiver Module...\n");
	pthread_cancel(receiverThread);
	pthread_join(receiverThread, NULL);	
}