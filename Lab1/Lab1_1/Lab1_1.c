#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int charToInt(char *obj){
    int result=0;
    while(*obj){        
        result=result*10+(int)(*obj-48);      
        obj++;
    }
    return result;
}

int chkArgc(int obj){
	if(obj<4) return 1;
	else return 0;
}

int main(int argc, char* argv[]) {
	
	if(chkArgc(argc)==1){
		printf("Please provide the input file name, output file name and chunksize.\n");
		exit(0);
	}

	int rfd, wfd, n, c_size = charToInt(argv[3]);
	char buf[10000];
	char *inputFile = argv[1], *outputFile = argv[2];
	
	if(c_size > 2048) {
		c_size = 2048;
		printf("Available maximum Chunk Size is 2048.\nSo Chunk Size changed to 2048!\n");
	}
	printf("Copy %s to %s (Chunk size = %d)\n", inputFile, outputFile, c_size);

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

	clock_t start = clock();
    	while ((n = read(rfd, buf, c_size)) > 0)
		if (write(wfd, buf, n) != n) perror("Write");
	clock_t end = clock();

    	if (n == -1) perror("Read");


    	close(rfd);
	close(wfd);

	printf("It takes %lf seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

    	return 0;
}
