#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	if(argc != 3){
		printf("Guide : <program name> <input file> <output file>\n");
		exit(1);
	}

	int inputFile = open(argv[1], O_RDONLY);

	if(inputFile == -1){
		perror("File Open");
		exit(1);
	}

	FILE* outputFile = fopen(argv[2], "w");

	while(1){
		unsigned char buf1, buf2, buf3;
		if( read(inputFile, &buf1, 1) <=0 ) break;
		read(inputFile, &buf2, 1);
		read(inputFile, &buf3, 1);
		printf("%u ", ((unsigned int)buf1 << 16) + ((unsigned int)buf2 << 8) + (unsigned int)(buf3));
		printf("%d %d %d \n", buf1, buf2, buf3);
		fprintf(outputFile, "%u ", ((unsigned int)buf1 << 16) + ((unsigned int)buf2 << 8) + (unsigned int)(buf3));
	}

	printf("\n");
	fprintf(outputFile, "\n");

	close(inputFile);
	fclose(outputFile);

	return 1;
}
