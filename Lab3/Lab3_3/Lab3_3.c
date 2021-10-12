#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int equal(char *obj1, char *obj2){
	while(*obj1 && *obj2){
		if(*obj1 != *obj2) return 0;
		obj1++;
		obj2++;
	}
	if('0' <= *obj1 && *obj1 <= '9') return 1;
	else return 0;
}

int charToInt(char *obj){
	int result=0;
	while(*obj){        
		result=result*10+(int)(*obj-48);      
		obj++;
	}
	return result;
}

int main(int argc, char* argv[]){
	DIR *dp;
	struct dirent *dent;

	if (argc != 4){
		exit(1);
	}

	clock_t start = clock();

	int step = charToInt(argv[2]);

	char* outputFolder = argv[3];

	//split argv[1] to directory and prefix
	char path[100] = {0};
	char prefix[100] = {0};
	int i = 0, j, chk;
	while(*(argv[1]+i)){
		if(*(argv[1]+i) == '/'){
			chk = i;
		}
		i++;
	}
	int argvSize = i;
	for(i=0;i<=chk;i++) path[i]= *(argv[1]+i);
	if ((dp = opendir(path)) == NULL) {
		perror(path);
		exit(1);
	}
	j = 0;
	for(i=chk+1;i<argvSize;i++){
		prefix[j++] = *(argv[1]+i);
	}

	//set outputpath
	char outputPath[1001] = {0};
	for(i=0;i<=chk;i++) outputPath[i]= *(argv[1]+i);
	j = 0;
	while(*(argv[3]+j)){
		outputPath[i] = *(argv[3]+j);
		i++;
		j++;
	}
	if (mkdir(outputPath, 0755) == -1){
		perror(outputPath);
		exit(1);
	}

	outputPath[i++]='/';
	j = 0;
	while(*(prefix+j)){
		outputPath[i] = *(prefix+j);
		i++;
		j++;
	}

	int cnt = 1;
	int num = i;
	seekdir(dp,2);
	while (dent = readdir(dp)){

		if(equal(dent->d_name, prefix) == 0) continue;

		if(cnt < 10){
			outputPath[num]='0';
			outputPath[num+1]='0';
			outputPath[num+2]='0'+cnt;
		}
		else if(10 <= cnt && cnt < 100){
			outputPath[num]='0';
			outputPath[num+1]='0' + (cnt/10);
			outputPath[num+2]='0' + (cnt%10);
		}
		else{
			outputPath[num]='0' + (cnt/100);
			outputPath[num+1]='0' + (cnt%100/10);
			outputPath[num+2]='0' + (cnt%10);
		}
		if (symlink(dent->d_name, outputPath) == -1){
			perror(outputPath);
			exit(1);
		}
		seekdir(dp, telldir(dp) + step - 1);
		cnt++;
	}

	closedir(dp);

	if (cnt == 1){
		printf("Please check prefix..\n");
		exit(1);
	}

	clock_t end = clock();

	printf("Sampling complete!\nIt takes %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

	return 1;
}
