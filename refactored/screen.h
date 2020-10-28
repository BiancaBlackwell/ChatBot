#ifndef _SCREEN_H_
#define _SCREEN_H_

#define MSG_MAX_LEN 1024

#include "list.h"
#include "input.h"
#include "receiver.h"
#include "sender.h"

void init_screen(void* unused);
void* display(void* unused);
void close_screen(void* unused);



#endif