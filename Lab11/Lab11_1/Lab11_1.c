#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

FILE *fp;

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int initsem(key_t semkey){
    union semun semunarg;
    int status = 0, semid;

    semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semid == -1){
        if (errno == EEXIST){
            semid = semget(semkey, 1, 0);
        }
    }
    else {
        semunarg.val = 1;
        // status = semctl(semid, 0, SETVAL, semunarg); //1로 초기화
        status = semctl(semid, 0, SETVAL, 1); //1로 초기화
    }

    if (semid == -1 || status == -1){
        perror("initsem");
        return -1;
    }

    return semid;
}

int semlock(int semid){
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1){
        perror("semlock failed");
        exit(1);
    }
    return 0;
}

int semunlock(int semid){
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1){
        perror("semunlock failed");
        exit(1);
    }
    return 0;
}

void semhandle(){

    int semid;
    if ((semid = initsem(1)) < 0) exit(1);

    semlock(semid);

    sleep(1);
    printf("%d번 손님 대기 등록 완료했습니다.\n", (int)getpid());
    fprintf(fp, "%d ", (int)getpid());
    semunlock(semid);
    exit(0);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Guide : <Program name> <# of processes>\n");
        exit(0);
    }
    fp = fopen("paper.txt", "w");
    for (int i = 0; i < atoi(argv[1]); i++)
        if(fork() == 0) semhandle();

    while( wait(NULL) != -1 );

    return 0;
}