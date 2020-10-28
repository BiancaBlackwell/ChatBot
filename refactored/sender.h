#ifndef _SENDER_H_
#define _SENDER_H_

#define MSG_MAX_LEN 1024

#include "list.h"
#include "input.h"
#include "receiver.h"
#define PORT 22110
#define fPORT 21210

void init_sender(void* unused);
void* sender(void* unused);
void close_sender(void* unused);



#endif