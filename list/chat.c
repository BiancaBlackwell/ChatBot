//Bianca Blackwell 301 304 375 - CMPT 300 Assignment 2
#include "list.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <netdb.h>


#define MSG_MAX_LEN 1024
#define PORT 22110

static int socketDescriptor;

bool check_input(int argCount, char** args){
	//verify we were given the necesary info by user
	bool valid = false;
	if(argCount == 3){
		valid = true;
	}
	//check actual args by args[i]
	return valid;
}

void* receiveThread(void* unused){
	//Address
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htons(INADDR_ANY);
	sin.sin_port = htons(PORT);

	//Create UDP socket
	socketDescriptor = socket(PF_INET, SOCK_DGRAM,0);
	bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

	while(1){
		//get data (blocking)
		//change address sent to client

		struct sockaddr_in sinRemote;
		unsigned int sin_len = sizeof(sinRemote);
		char messageRx[MSG_MAX_LEN];
		recvfrom(socketDescriptor, messageRx, MSG_MAX_LEN, 0, (struct sockaddr*)&sinRemote, &sin_len);

		//do something with the message
		printf("MESSAGE RECEIEVED! %s\n", messageRx);
	}

	printf("Done rx thread!");
	return NULL;
}

//function for monitoring stdin and add to outgoing
//function for monitoring the incoming list to display to stdout
//function for monitoring the outgoing list to send a message
//function for monitoring the socket to see if we get anything and add to incoming

int main(int argCount, char** args){
	printf("Starting...\n");
	if(!check_input(argCount,args)) return -1;

	struct List_s *outgoing = List_create(); //for messages that are to be sent
	struct List_s *incoming = List_create(); //for messages that are recieved

	/*
	//TEST list.o success! This works.

	char message[] = "Hello my name is Bob";
	List_add(outgoing,message);


	char* currentmessage = List_remove(outgoing);

	printf("%s \n", currentmessage);
	*/


	//create a socket (myPC end) and connect with (with netcat?) try to send out a message

	//print waiting for other user [wait here until you recieve any kind of response]

	//create four threads [stdout, stdin, UDPout, UDPin]
	pthread_t outputScreen;
	pthread_create(&outputScreen, NULL, receiveThread, NULL);


	pthread_join(outputScreen, NULL);

	//program all those threads for their respective tasks



	printf("Done!\n");
	return 0;
}