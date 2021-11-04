#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid1 = fork();
    if (pid1 > 0){
        pid_t pid2 = fork();
        if (pid2 > 0){
            int status;
            while (wait(&status) != pid2){
                continue;
            }
            while (wait(&status) != pid1){
                continue;
            }
            printf("Parent Process\n");
            printf("My Child's PID : %d, %d\n",pid1, pid2);
            printf("My PID : %d\n", (int)getpid());
            printf("My Parent's PID : %d\n", (int)getppid());
        }
        else {
            printf("Second Child Process\n");
            printf("My PID : %d\n", (int)getpid());
            printf("My Parent's PID : %d\n\n", (int)getppid());
        }
    }
    else{
        sleep(1);
        printf("First Child Process\n");
        printf("My PID : %d\n", (int)getpid());
        printf("My Parent's PID : %d\n\n", (int)getppid());
    }
}