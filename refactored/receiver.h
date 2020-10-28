#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#define MSG_MAX_LEN 1024
#define MAXLINE 1000 //temp testing sockets

#include "list.h"
#include "input.h"
#include "sender.h"

void init_receiver(void* unused);
void* receiver(void* unused);
void close_receiver(void* unused);

#endif