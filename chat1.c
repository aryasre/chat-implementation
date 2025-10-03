#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "chat.h"


int main()
{
    key_t key = ftok(FTOK_PATH,FTOK_PROJ_ID);
    if(key == (key_t)-1)
    {
        die("ftok");
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) die("msgget");

    struct msgbuf msg;

    printf("Chat1 started. Type messages (Ctrl+C to quit):\n");

    while (1) {
        // Send message to Chat2
        msg.mtype = 2;   // Send to process 2
        strcpy(msg.sender, "Sender");

        printf("Hi How are you?");

        fflush(stdout);
        if (!fgets(msg.text, MAX_TEXT, stdin)) break;
        msg.text[strcspn(msg.text, "\n")] = 0; // remove newline

        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            die("msgsnd");
        }

        // Receive reply from Chat2
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
           die("msgrcv");
        }
        printf("%s: %s\n", msg.sender, msg.text);
    }

    return 0;
}
