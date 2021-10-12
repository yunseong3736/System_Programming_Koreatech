#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int chkBigger(int a, int b){
	if(a>b) return 1;
	else if(a==b) return 0;
	else if(a<b) return -1;
}

int main(int argc, char* argv[]){
	
	if(argc != 3){
		printf("Guide : <programe name> <file1 name> <file2 name>\n");
		exit(1);
	}

	struct stat file1, file2;

	if(stat(argv[1], &file1) == -1) {
		perror("File stat failed!");
		exit(1);
	}
	if(stat(argv[2], &file2) == -1) {
		perror("File stat failed!");
		exit(1);
	}
	
	switch( chkBigger((int)file1.st_size,(int)file2.st_size) ){
		case 1:
			printf("%s is bigger.\n", argv[1]);
			if( access(argv[1], R_OK) == 0) printf("%s : Read permission is permitted.\n", argv[1]);
			else printf("%s : Read permission is not permitted.\n", argv[1]);
			break;
		case -1:
			printf("%s is bigger.\n", argv[2]);
			if( access(argv[2], R_OK) == 0) printf("%s : Read permission is permitted.\n", argv[2]);
			else printf("%s : Read permission is not permitted.\n", argv[2]);
			break;
		case 0:
			printf("%s and %s have same size.\n", argv[1], argv[2]);
			if( access(argv[1], R_OK) == 0) printf("%s : Read permission is permitted.\n", argv[1]);
			else printf("%s : Read permission is not permitted.\n", argv[1]);
			if( access(argv[2], R_OK) == 0) printf("%s : Read permission is permitted.\n", argv[2]);
			else printf("%s : Read permission is not permitted.\n", argv[2]);
			break;
		default:
			break;
	}

	return 1;
}
