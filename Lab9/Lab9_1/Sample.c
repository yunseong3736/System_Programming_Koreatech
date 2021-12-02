#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int fd;
    pid_t pid;
    char buf[257];
    int len, status;

    printf("무~한~~~~~~!\n");

    scanf("%s", buf);

    sleep(1);

    printf("%s\n", buf);

    return 1;
}