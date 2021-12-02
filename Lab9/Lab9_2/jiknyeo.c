#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int getint(char *obj){
    
    int result = 0;
    while(*obj){
        result *= 10;
        result += (*obj) - '0';
        obj++;
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    
    if (argc != 3){
        printf("Guide : <Program name> <Message> <Number of repeats>\n");
        exit(1);
    }

    mkfifo("./pipeFile", 0644);

    int pd, n = getint(argv[2]);
    char *msg = argv[1];

    printf("직녀 ========\n");
    if ( (pd = open("./pipeFile", O_WRONLY)) == -1){
        perror("open");
        exit(1);
    }

    write(pd, &n, 1);

    for (int i = 0; i < n; i++){
        printf("견우에게 : %s\n", msg);
        write(pd, msg, strlen(msg) + 1);
        sleep(1);
    }

    close(pd);

    return 0;
}