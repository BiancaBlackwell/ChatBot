#ifndef _INPUT_H_
#define _INPUT_H_

#define MSG_MAX_LEN 1024
#include "list.h"
#include "input.h"
#include "receiver.h"
//todo: add functions here!
#define PORT 22110
#define fPORT 21210

void init_input(void* unused);
void* listener(void* unused);
void close_input(void* unused);



#endif