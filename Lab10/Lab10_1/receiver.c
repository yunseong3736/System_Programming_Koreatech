#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf
{
    /* data */
    long mtype;
    char mtext[100];
};

int main(void){
    key_t key;
    int msgid, len, mode;
    struct mymsgbuf msg;
    struct msqid_ds stat;

    key = ftok("keyfile", 1);
    msgid = msgget(key, 0);
    if (msgid < 0){
        perror("msgget");
        exit(1);
    }
    if (msgctl(msgid, IPC_STAT, &stat) == -1){
        perror("msgctl");
        exit(1);
    }
    while(1){
        
        printf("메일 수 (%d)\n", stat.msg_qnum);
        printf("1.받은 메일 읽기\n2.새로고침\n3.종료\n>>> ");
        scanf("%d", &mode);

        if (mode == 1){
            if (stat.msg_qnum == 0){
                printf("읽을 메일이 없습니다!!\n");
                continue;
            }
            for (int i = 0; i < stat.msg_qnum; i++){
                msgrcv(msgid, &msg, 100, 0, 0);
                printf("-> %s\n", msg.mtext);
                if (i == stat.msg_qnum - 1)
                    printf("by [보낸이 PID : %d]\n", stat.msg_lspid);
            }
            if (msgctl(msgid, IPC_STAT, &stat) == -1){
                perror("msgctl");
                exit(1);
            }
        }
        else if (mode == 2){
            if (msgctl(msgid, IPC_STAT, &stat) == -1){
                perror("msgctl");
                exit(1);
            }
        }
        else if (mode == 3){
            break;
        }
        else {
            printf("1, 2, 3 중에 선택하시오.\n");
        }
    }

    return 0;
}