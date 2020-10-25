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
	if(!check_intput(argCount,args)) return -1;

	List_s outgoing; //for messages that are to be sent
	List_s incoming; //for messages that are recieved

	List_add(outgoing,"Hello my name is Bob");

	printf("%s \n", List_curr(outgoing));



	return 0;
}