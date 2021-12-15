#include <sys/types.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    key_t key;
    int shmid;
    int *shmaddr;
    sigset_t mask;

    key = ftok("shmfile", 1);
    shmid = shmget(key, 1024, IPC_CREAT|0666);
    
    shmaddr = shmat(shmid, NULL, 0);

    int currentPhase = 0, currentPosition;
    while(1){
        currentPosition = shmaddr[1];
        if (currentPhase != shmaddr[0]){
            currentPhase = shmaddr[0];
            printf("Phase : %d |A", currentPhase);
            for (int i = 0; i < currentPosition; i++) printf("=");
            printf("||");
            for (int i = 20; i > currentPosition; i--) printf("=");
            printf("B\n");
        }
        if (currentPosition <= 0 || currentPosition >= 20) break;
    }

    if (currentPosition == 0) printf("A team win!\n");
    if (currentPosition == 20) printf("B team win!\n");
    
    shmdt(shmaddr);

    return 0;
}