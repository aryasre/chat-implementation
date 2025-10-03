#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "chat.h"

int main() {
    key_t key = ftok(FTOK_PATH, FTOK_PROJ_ID);
    if (key == -1) {die("ftok") }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {die("msgget") }

    struct msgbuf msg;

    printf("Chat2 started. Type messages (Ctrl+C to quit):\n");

    while (1) {
        // Receive from Chat1
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 2, 0) == -1) {
            die("msgrcv");
        }
        printf("%s: %s\n", msg.sender, msg.text);

        // Send reply to Chat1
        msg.mtype = 1;  // Send back to process 1
        strcpy(msg.sender, "Receiver");

        printf("Hello I am good");
        fflush(stdout);
        if (!fgets(msg.text, MAX_TEXT, stdin)) break;
        msg.text[strcspn(msg.text, "\n")] = 0;

        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}
