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
    int msgid, mode;
    struct mymsgbuf msg;

    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT|0644);

    if (msgid == -1){
        perror("msgget");
        exit(1);
    }

    msg.mtype = 1;
    while(1){
        printf("1.메일 입력\n");
        printf("2.종료\n");
        printf(">>> ");
        scanf("%d", &mode);
        getchar();
        if (mode == 1){
            printf("메시지를 입력하세요 : ");
            gets(msg.mtext);
            if (msgsnd(msgid, (void*)&msg, 100, 0) == -1){
                perror("msgsnd");
                exit(1);
            }
        }
        else if (mode == 2)
            break;
        else
            printf("1과 2중에 선택하시오.\n");
    }

    return 0;
}