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
    struct msqid_ds stat;

    char* quiz[3] = {"1 더하기 1은?", "2 더하기 2는?", "조윤성의 학번은?"};
    char* answer[3] = {"2", "4", "2017136122"};

    key = ftok("keyfile", 1);
    msgid = msgget(key, IPC_CREAT|0644);

    if (msgid == -1){
        perror("msgget");
        exit(1);
    }
    printf("ㅇㅅㅁ 오징어 게임 시작 ㅇㅅㅁ\n\n");
    for (int i = 0; i < 3; i++){
        
        printf("%d 라운드 문제 전송\n", i + 1);
        msg.mtype = 1;
        strcpy(msg.mtext, quiz[i]);
        if (msgsnd(msgid, (void*)&msg, 100, 0) == -1){
            perror("msgsnd");
            exit(1);
        }
        if (msgrcv(msgid, (void*)&msg, 100, 2, 0) == -1){
            perror("msgrcv");
            exit(1);
        }

        if (strcmp(answer[i], msg.mtext) == 0){
            if (msgctl(msgid, IPC_STAT, &stat) == -1){
                perror("msgctl");
                exit(1);
            }
            printf("성공!\n%d번 참가자 %d라운드 통과\n", (int)stat.msg_lspid, i+1);
            msg.mtype = 1;
            strcpy(msg.mtext, "Success");
            if (msgsnd(msgid, (void*)&msg, 100, 0) == -1){
                perror("msgsnd");
                exit(1);
            }
        }
        else {
            printf("탕\nKilled\n");
            msg.mtype = 1;
            strcpy(msg.mtext, "Wrong");
            if (msgsnd(msgid, (void*)&msg, 100, 0) == -1){
                perror("msgsnd");
                exit(1);
            }
            break;
        }

    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}