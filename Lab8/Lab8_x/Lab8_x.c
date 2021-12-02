#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

#define CHECK_MMAP_SUCCESS(_addr) \
    if (_addr == MAP_FAILED)      \
    {                             \
        perror("mmap");           \
        exit(1);                  \
    }

caddr_t message, flag;

void stopHandler(){
    flag[0] = '\0';
    message[0] = '\0';
    printf("\n");
    exit(1);
}

int main(int argc, char *argv[]){

    signal(SIGINT, stopHandler);

    char* userName = "Guest";
    if (argc == 2){
        userName = argv[1];
    }

    // printf("%s ", userName);

    int fd1, fd2, myFlag, i;
    char file1[255] = "message.dat";
    char file2[255] = "flag.dat";
    char aux[255];
    char* auxp;
    
    if ((fd1 = open(file1, O_RDWR)) == -1){
        if ((fd1 = open(file1, O_RDWR | O_CREAT, 0644)) == -1){
            perror("open");
            exit(1);
        }
        ftruncate(fd1, 10000000);
    }
    if ((fd2 = open(file2, O_RDWR)) == -1){
        if ((fd2 = open(file2, O_RDWR | O_CREAT, 0644)) == -1){
            perror("open");
            exit(1);
        }
        ftruncate(fd2, 2);
    }

    int pageSize = getpagesize();
    
    message = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, (off_t)0);
    flag = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, (off_t)0);
    CHECK_MMAP_SUCCESS(message);
    CHECK_MMAP_SUCCESS(flag);
    close(fd1);
    close(fd2);

    if (flag[0] == '\0'){
        flag[0] = '0';
        myFlag = 0;
    }
    else {
        myFlag = 1;
    }
    // printf("[%d]\n",myFlag);
    while(1){
        if (flag[0] - '0' == myFlag){
            if (message[0] != '\0'){
                puts(message);
            }
            printf(": ");

            gets(aux);
            
            i = 0;
            auxp = userName;
            message[i++] = '[';
            while(*auxp){
                message[i++] = *auxp;
                auxp++;
            }
            message[i++] = ']';
            message[i++] = ' ';
            auxp = aux;
            while(*auxp){
                message[i++] = *auxp;
                auxp++;
            }
            message[i] = '\0';
            flag[0] = (myFlag + 1) % 2 + '0';
        }
    }
}