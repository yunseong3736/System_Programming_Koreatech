#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int checkLen(char *obj){
	int result = 0;
	while(*obj){
		result += 1;
		obj++;
	}
	return result;
}

int chkArgc(int obj){
	if(obj<3) return 1;
	else return 0;
}

int main(int argc, char* argv[]) {
	
	if(chkArgc(argc)==1){
		printf("Please provide the <Input file name> and <Target word>.\n");
		exit(0);
	}

	int rfd, wfd, n, targetLen = checkLen(argv[2]);
	char* buf;
	char* inputFile = argv[1];
	char* target = argv[2];

    	rfd = open(inputFile, O_RDONLY);
	if(rfd == -1) {
		perror(inputFile);
		exit(1);
	}

	printf("The target word is '%s' (size = %d)\n", target, targetLen);
	
	int cnt = 0, chk = -1;
	int targetCount = 0;

	clock_t start = clock();
	
    	while ( read(rfd, buf, 1) > 0){
		
		if( *buf == '\n') continue;
		if( chk == -1 ){
			printf("Compare the : ");
			chk = 0;
		}

		if( *buf!=' ' && *buf!='.' && *buf!='?' && *buf!=';' && *buf!='/' && *buf!=',' && *buf!='!' && *buf!='~' && *buf!=':' && *buf!=')' && *buf!='('){
			printf("%s", buf);
			if(chk == 0){
				if(*buf == target[cnt] && cnt!=targetLen) cnt++;
				else chk = 1;
			}
		}
		else{
			if(cnt == targetLen && chk == 0){
				printf(" - Matched!\n");
				targetCount++;
			}
			else{
				printf("\n");
			}
			cnt = 0;
			chk = -1;
		}
	}
	clock_t end = clock();

    	if (n == -1) perror("Read");


    	close(rfd);
	close(wfd);
	printf("# of '%s' in the text file is %d\n", target, targetCount);
	printf("It takes %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

    	return 0;
}
