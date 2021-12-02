#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf
{
    /* data */
    long mtype;
    char mtext[80];
};

int main(void){
    key_t key;
    int msgid, len;
    struct mymsgbuf inmsg;

    key = ftok("keyfile", 1);
    msgid = msgget(key, 0);
    if (msgid < 0){
        perror("msgget");
        exit(1);
    }    
    
    len = msgrcv(msgid, &inmsg, 80, 0, 0);
    printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len);

    return 0;
}