//Bianca Blackwell 301 304 375 - CMPT 300 Assignment 2
#include "list.h"
#include <stdio.h>

bool check_input(int argCount, char** args){
	//verify we were given the necesary info by user
	bool valid = false;
	if(argCount == 3){
		valid = true;
	}
	//check actual args by args[i]
	return valid;
}


int main(int argCount, char** args){
	if(!check_input(argCount,args)) return -1;

	struct List_s outgoing; //for messages that are to be sent
	struct List_s incoming; //for messages that are recieved

	char message[] = "Hello my name is Bob";
	printf("Adding...\n");
	List_add(&outgoing,message);
	printf("Added message to list\n");


	char* currentmessage = List_curr(&outgoing);
	printf("Recieved current message\n");

	//I think i'm seg faulting here? But i need to figure out a way to display lol
	printf("%s \n", *currentmessage);
	printf("Ending Program <3\n");


	return 0;
}