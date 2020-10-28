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
struct List_s *incoming;
#define PORT 22110

void init_screen(void* unused){
	pthread_create(&displayThread, NULL, display, NULL);
}
void* display(void* unused){
	printf("Starting Screen Module...\n");

}
void close_screen(void* unused){
	printf("Shutting down Screen Module...\n");
	pthread_cancel(displayThread);
	pthread_join(displayThread, NULL);	
}