#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

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

    if (argc != 3){
        printf("Guide : <Start number> <End number>\n");
        exit(1);
    }
    time_t ltime;
    int startN = getint(argv[1]);
    int endN = getint(argv[2]);
    time(&ltime); 
    printf("[Serial start] %s", ctime(&ltime));
    
    int n, i, flag = 0, cnt = 0;
    
    for (n = startN; n <= endN; n++){
        flag = 0;
        for (i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0 && n != 1)
            cnt++;
    }

    printf("[Serial] found %d primes\n", cnt);
    time(&ltime);
    printf("[Serial end] %s", ctime(&ltime));

    time(&ltime); 
    printf("[Parallel start] %s", ctime(&ltime));
    pid_t pid = fork();
    if (pid == 0){
        struct timeval start, end;
        cnt = 0;
        gettimeofday(&start, NULL);
        for (n = startN; n <= (startN + endN) / 2; n++){
            flag = 0;
            for (i = 2; i <= n / 2; i++) {
                if (n % i == 0) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && n != 1)
                cnt++;
        }
        gettimeofday(&end, NULL);
        printf("[PID = %d] I found %d prime numbers between (%d ~ %d)\n", pid, cnt, startN, (startN + endN) / 2);
        printf("[PID = %d] takes %.2lf ms\n", pid, (end.tv_usec - start.tv_usec)/1000.0 + (end.tv_sec - start.tv_sec)*1000);
        time(&ltime); 
        printf("[Proc.%d end] %s", pid, ctime(&ltime));
    }
    else{
        struct timeval start, end;
        cnt = 0;
        gettimeofday(&start, NULL);
        for (n = (startN + endN) / 2 + 1; n <= endN; n++){
            flag = 0;
            for (i = 2; i <= n / 2; i++) {
                if (n % i == 0) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0 && n != 1)
                cnt++;
        }
        gettimeofday(&end, NULL);
        
        int status;
        while (wait(&status) != pid)continue;
        printf("[PID = %d] I found %d prime numbers between (%d ~ %d)\n", pid, cnt, (startN + endN) / 2 + 1, endN);
        printf("[PID = %d] takes %.2lf ms\n", pid, (end.tv_usec - start.tv_usec)/1000.0 + (end.tv_sec - start.tv_sec)*1000);
        time(&ltime); 
        printf("[Proc.%d end] %s", pid, ctime(&ltime));
    }

    return 1;
}