#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define CHECK_MMAP_SUCCESS(_addr) \
    if (_addr == MAP_FAILED)      \
    {                             \
        perror("mmap");           \
        exit(1);                  \
    }

int main(int argc, char *argv[]){
    int fd;
    caddr_t user1;
    char fileName[255] = "temp.dat";
    char aux[255];
    char* auxp;
    
    if ((fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1){
        perror("open");
        exit(1);
    }
    ftruncate(fd, 100);
    int pageSize = getpagesize();
    
    user1 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    CHECK_MMAP_SUCCESS(user1);
    
    printf("[발신] ");
    scanf("%s", aux);
    auxp = aux;
    
    int i = 0;
    while(*auxp){
        user1[i++] = *auxp;
        printf("%c\n", *auxp);
        auxp++;
    }
    user1[i] = '\0';
    printf("%s\n", user1);

    close(fd);
}