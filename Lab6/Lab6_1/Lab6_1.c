#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc != 3 ) {
        printf("Check arg!\n");
        exit(1);
    }

    if (execlp("gcc", "gcc", "-o", argv[2], argv[1], (char *)NULL) == -1){
        perror("execlp");
        exit(1);
    }

    return 0;
}