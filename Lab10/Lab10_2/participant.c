#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf
{
    long mtype;
    char mtext[100];
};

int main(void){
    key_t key;
    int msgid;
    struct mymsgbuf msg;
    struct msqid_ds stat;

    key = ftok("keyfile", 1);
    msgid = msgget(key, 0);
    if (msgid == -1){
        perror("msgget");
        exit(1);
    }

    printf("ㅇㅅㅁ 당신은 오징어 게임에 참가하셨습니다 ㅇㅅㅁ\n\n");
    for (int i = 0; i < 3; i++){
        
        msg.mtype = 1;
        if (msgrcv(msgid, (void*)&msg, 100, 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        printf("%d라운드 -> ", i + 1);
        printf("%s : ", msg.mtext);
        scanf("%s", msg.mtext);

        msg.mtype = 2;
        if (msgsnd(msgid, (void*)&msg, 100, 0) == -1){
                perror("msgsnd");
                exit(1);
        }

        msg.mtype = 1;
        if (msgrcv(msgid, (void*)&msg, 100, 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if (strcmp(msg.mtext, "Wrong") == 0){
            printf("Killed\n");
            exit(1);
        }

    }

    printf("456억원 획득!!\n");

    return 0;
}