#ifndef CHAT_H
#define CHAT_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 128
#define FTOK_PATH "chatfile"   // create an empty file named "chatfile"
#define FTOK_PROJ_ID 65

// Message structure
struct msgbuf {
    long mtype;                 // message type 
    char sender[32];            // sender name
    char text[MAX_TEXT];        // message text
};


static void die(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

#endif
