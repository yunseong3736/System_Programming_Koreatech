#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
    int fd;
    caddr_t user2;
    char fileName[255] = "temp.dat";
    char* aux;
    
    if ((fd = open(fileName, O_RDWR)) == -1){
        perror("open");
        exit(1);
    }
    int pageSize = getpagesize();

    user2 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    close(fd);

    printf("[수신] %s", user2);
}