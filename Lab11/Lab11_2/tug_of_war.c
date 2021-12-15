#include <sys/types.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) {
    key_t key;
    int shmid;
    int *shmaddr;
    sigset_t mask;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT|0666);
    
    shmaddr = shmat(shmid, NULL, 0);
    shmaddr[0] = 0;
    shmaddr[1] = 10;

    srand((unsigned int)time(NULL));
    int powerA = 6, powerB = 3, phasePower;
    sleep(2);
    while(1){
        phasePower = powerB - powerA;
        //phase 증가
        shmaddr[0] += 1;
        //줄다리기 게임 상황
        shmaddr[1] += phasePower;
        if (shmaddr[1] >= 20){
            shmaddr[1] = 20;
            break;
        }
        if (shmaddr[1] <= 0){
            shmaddr[1] = 0;
            break;
        }
        powerA -= (rand() % 2);
        powerB += (rand() % 2);
        sleep(2);
    }
    
    shmdt(shmaddr);

    return 0;
}