#include <stdlib.h>
#include <stdio.h>

int main(void) {
    
    FILE *fp;
    char buf[256];

    fp = popen("./Sample.out", "w");
    
    if (fp == NULL){
        fprintf(stderr, "popen failed\n");
        exit(1);
    }

    fputs("무~야~호~~~~~~!", fp);
    fputc('\n', fp);

    pclose(fp);

    return 0;
}