#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int cnt;

void cHandler(){
    if (cnt == 0){
        printf("형님 먼저\n");
    }
    else {
        printf("아우 먼저\n");
    }
    cnt = (cnt+1) % 2;
}

void zHandler(){
    if (cnt == 0){
        printf("알았어 형님\n");
    }
    else {
        printf("알았어 아우\n");
    }
    exit(0);
}

int main(int argc, char* argv[]){

    cnt = 0;
    
    signal(SIGINT, cHandler); //Ctrl + C
    signal(SIGTSTP, zHandler); //Ctrl + Z

    printf("형님 먼저\n");
    cnt++;

    for (;;){
        pause();
    }

    return 1;
}