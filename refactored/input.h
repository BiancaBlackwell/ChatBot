#ifndef _INPUT_H_
#define _INPUT_H_

#define MSG_MAX_LEN 1024
#include "list.h"
//todo: add functions here!

void init_input(void* unused);
void new_input(char *message, List* outgoing);
void* listener(void* unused);
void close_input(void* unused);



#endif