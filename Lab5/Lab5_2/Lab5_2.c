#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

int charToInt(char *obj){
    int result=0;
    while(*obj){        
        result = result*10+(int)(*obj-48);
        obj++;
    }
    return result;
}

int main(int argc, char* argv[]) {
	
	if(argc != 3){
		printf("Guide : <program name> <input file name> <output file name>\n");
		exit(0);
	}

	int rfd, wfd, n;
	char buf[20];
	char *inputFile = argv[1], *outputFile = argv[2];

    clock_t t1, t2;
    struct tms mytms;

	rfd = open(inputFile, O_RDONLY);
    if(rfd == -1) {
		perror(inputFile);
		exit(1);
	}
	wfd = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (wfd == -1) {
		perror(outputFile);
		exit(1);
	}

    t1 = times(&mytms);

	while ((n = read(rfd, buf, 16)) > 0)
		if (write(wfd, buf, n) != n) perror("Write");
	
    t2 = times(&mytms);

    if (n == -1) perror("Read");


    close(rfd);
	close(wfd);

	printf("Real time : %.2f sec\n", (double)(t2-t1)/sysconf(_SC_CLK_TCK));
    printf("User time : %.2f sec\n", (double)mytms.tms_utime/sysconf(_SC_CLK_TCK));
    printf("System time : %.2f sec\n", (double)mytms.tms_stime/sysconf(_SC_CLK_TCK));
    int result = (double)mytms.tms_utime/sysconf(_SC_CLK_TCK) * 100 + (double)mytms.tms_stime/sysconf(_SC_CLK_TCK) * 200;
    printf("사용료는 %d원 입니다.\n", result);

    return 0;
}
