#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int seconds;
int cnt;

void stopHandler(){
    printf("Cannot generate the interrupt character (Ctrl + C, Ctrl + Z) !!\n");
}
void alarmHandler(){
    cnt++;
    printf("%d seconds...\n", cnt);

    if (cnt == seconds){
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        printf("Now we can generate the interrupt character (Ctrl + C, Ctrl + Z) !!\n");
    }
    else {
        alarm(1);
    }
}

int getint(char *obj){
    int result = 0;
    while(*obj){
        result *= 10;
        result += (*obj) - '0';
        obj++;
    }
    
    return result;
}

int main(int argc, char* argv[]){

    seconds = getint(argv[1]);

    printf("For %d second(s), we cannot generate the interrupt character (Ctrl + C, Ctrl + Z) !!\n", seconds);

    signal(SIGINT, stopHandler);
    signal(SIGTSTP, stopHandler);
    signal(SIGALRM, alarmHandler);

    alarm(1);

    for (;;){
        pause();
    }

    return 1;
}