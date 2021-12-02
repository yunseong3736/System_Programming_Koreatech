#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void response(char *obj){
    write(1, "직녀에게:", 13);
    if (strcmp(obj, "ping") == 0){
        write(1, "pong\n", 5);
    }
    else if (strcmp(obj, "tiki") == 0){
        write(1, "taka\n", 5);
    }
    else {
        write(1, "what?\n", 6);
    }
}

int main(void) {
    
    mkfifo("./pipeFile", 0644);

    int pd, n, aux;
    char inmsg[80];

    printf("견우 ========\n");
    if ( (pd = open("./pipeFile", O_RDONLY)) == -1){
        perror("open");
        exit(1);
    }

    read(pd, &n, 1);

    for (int i = 0; i < n; i++){
        while ( (aux = read(pd, inmsg, 80)) > 0){
            break;
        }
        response(inmsg);
        // sleep(1);
    }

    close(pd);

    return 0;
}