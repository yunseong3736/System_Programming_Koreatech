#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define chkPrimeN(n){\
    flag = 0;\
    if(n == 1) flag = 1;\
    else{\
        for (int i = 2; i <=n/2; i++){\
            if (n % i ==0){\
                flag = 1;\
                break;\
            }\
        }\
    }\
    if (flag == 0)\
        cnt++;\
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

int main(int argc, char *argv[]){

    if (argc != 5){
        printf("Guide : <Start number> <End number> <# of Process> <Output Filename>\n");
        exit(1);
    }

    time_t ltime;
    int startN = getint(argv[1]);
    int endN = getint(argv[2]);
    int procN = getint(argv[3]);
    int chkRange = (endN - startN + 1) / procN;
    int identityN = -1;
    int n, i, flag = 0, cnt = 0;

    FILE *outputFile = fopen(argv[4], "w");
    FILE** tmpFiles;
    tmpFiles = (FILE **)malloc(sizeof(FILE *) * procN);

    for (i = 0; i < procN; i++){
        tmpFiles[i] = tmpfile();
    }

    time(&ltime);
    pid_t pid = fork();
    identityN = 0;
    startN = endN - chkRange + 1;
    if(pid != 0){
        struct timeval start, end;
        int tmp;
        cnt = 0;
        gettimeofday(&start, NULL);
        for (n = startN; n <= endN; n++){
            chkPrimeN(n);
            if (flag == 0){
                fprintf(tmpFiles[0], "%d ", n);
            }
        }
        while (wait(NULL) != pid)continue;
        gettimeofday(&end, NULL);
        printf("[P%d] found %d primes\n", identityN, cnt);
        switch (procN)
        {
        case 1:
            printf("[Serial] takes %.2lf ms\n", (end.tv_usec - start.tv_usec)/1000.0 + (end.tv_sec - start.tv_sec)*1000);
            break;
        
        default:
            printf("[Parallel] takes %.2lf ms\n", (end.tv_usec - start.tv_usec)/1000.0 + (end.tv_sec - start.tv_sec)*1000);
            break;
        }
        
        for (i = procN - 1; i >= 0; i--){
            int tmp;
            rewind(tmpFiles[i]);
            while(fscanf(tmpFiles[i], "%d ", &tmp) > 0){
                fprintf(outputFile, "%d ", tmp);
            }
            fclose(tmpFiles[i]);
        }
        fprintf(outputFile, "\n");
        free(tmpFiles);
        fclose(outputFile);
    }
    else if (procN != 1){
        for (int p = 1; p < procN; p++){
            identityN = p;
            endN = startN - 1;
            startN = endN - chkRange + 1;
            if (p + 1 != procN) pid = fork();
            if (pid != 0) break;            
        }
        cnt = 0;
        if (pid == 0 && startN != getint(argv[1])) startN = getint(argv[1]);
        for (n = startN; n <= endN; n++){
            chkPrimeN(n);
            if (flag == 0){
                fprintf(tmpFiles[identityN], "%d ", n);
            }
        }
        while (wait(NULL) != pid && pid != 0)continue;
        printf("[P%d] found %d primes\n", identityN, cnt);
    }

    return 1;
}