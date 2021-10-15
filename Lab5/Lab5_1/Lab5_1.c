#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getint(char *obj){
    int result = 0;
    while(*obj){
        result *= 10;
        result += (*obj) - '0';
        obj++;
    }
    
    return result;
}

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Guide : <Program name> <PGID>\n");
        exit(1);
    }
    
    int pID = (int)getpid();
    int pgID = (int)getpgid(0);

    printf("PID : %d\nPGID : %d\n",pID,pgID);
    printf("-------------------\n");
    setpgid(pID, getint(argv[1]));
    pgID = (int)getpgid(0);
    printf("PID : %d\nPGID : %d\n",pID,pgID);

    while(1){
        continue;
    }

    return 1;
}