#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int chkArgc(int obj){
	if(obj<3) return 1;
	else return 0;
}

int main(int argc, char* argv[]){

	if(chkArgc(argc)==1){
		printf("Please provide the input file name, output file name.\n");
		exit(0);
	}

	char *encodedFile = argv[1];
	char *decodedFile = argv[2];
	char buf;

	int enFile, deFile;

	enFile = open(encodedFile, O_RDONLY);
	if (enFile == -1){
		perror(encodedFile);
		exit(1);
	}

	deFile = open(decodedFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (deFile == -1){
		perror(decodedFile);
		exit(1);
	}

	off_t fsize = lseek(enFile, 0, SEEK_END); //Check & remember file size
	lseek(enFile, 0, SEEK_SET); //Reset offset

	time_t start = time(NULL);
	while (read(enFile, &buf, 1) > 0) {
		if (32 <= buf && buf <= 127){
			printf("%c", buf);
			write(deFile, &buf, 1);
		}
		else{
			lseek(enFile, (int)buf % 32, SEEK_CUR); //Jump _value%32_ from current offset
		}
	}
	time_t end = time(NULL);

	printf("\nIt takes %lf seconds\n", (double)end-start);

	return 0;
}
