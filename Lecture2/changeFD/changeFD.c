#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd, flags;

    fd = open("linux.txt", O_RDWR);
    if (fd == -1){
        perror("Open linux.txt\n");
        exit(1);
    }

    if ( (flags = fcntl(fd, F_GETFL)) == -1 ){
        perror("Get flags\n");
        exit(1);
    }

    flags |= O_APPEND;

    if ( (flags = fcntl(fd, F_SETFL, flags)) == -1 ){
        perror("Set flags\n");
        exit(1);
    }

    if ( (write(fd, "KOREATECH", 9)) != 9 ){
        perror("Write sentences\n");
        exit(1);
    }

    close(fd);

    return 1;
}