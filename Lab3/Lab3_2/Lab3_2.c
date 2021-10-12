#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define YEAR 365 * 24 * 60 * 60
#define MONTH 30 * 24 * 60 * 60
#define DAY 24 * 60 * 60
#define HOUR 60 * 60
#define MINUTE 60

void timeStampToDate(long long int stamp){
	int year = 1970;
	int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	stamp += (9 * HOUR);
	
	while(stamp > YEAR){
		stamp -= YEAR;
		if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) stamp -= DAY;
		year += 1;
	}

	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) month[2] = 29;
	int m = 1;
	while(stamp > month[m] * DAY){
		stamp -= (month[m] * DAY);
		m += 1;
	}

	switch(m){
		case 1:
			printf(" Jan");
			break;
		case 2:
			printf(" Feb");
			break;
		case 3:
			printf(" Mar");
			break;
		case 4:
			printf(" Apr");
			break;
		case 5:
			printf(" May");
			break;
		case 6:
			printf(" Jun");
			break;
		case 7:
			printf(" Jul");
			break;
		case 8:
			printf(" Aug");
			break;
		case 9:
			printf(" Sep");
			break;
		case 10:
			printf(" Oct");
			break;
		case 11:
			printf(" Nov");
			break;
		case 12:
			printf(" Dec");
			break;
	}

	int daycnt = stamp / (DAY) + 1;
	stamp %= (DAY);
	printf(" %2d", daycnt);

	int hcnt = stamp / (HOUR);
	stamp %= (HOUR);
	printf(" %02d", hcnt);

	int mcnt = stamp / (MINUTE);
	stamp %= (MINUTE);
	printf(":%02d", mcnt);

} 

void printInfo(){

	struct dirent *dent;
	struct stat buf;
	DIR *dp;

	dp = opendir(".");
	seekdir(dp, 2);
	while(dent = readdir(dp)){
		
		stat(dent->d_name, &buf);
		
		if(S_ISREG(buf.st_mode)) printf("-");
		else if(S_ISDIR(buf.st_mode)) printf("d");
		else if(S_ISBLK(buf.st_mode)) printf("b");
		else if(S_ISCHR(buf.st_mode)) printf("c");
		else if(S_ISLNK(buf.st_mode)) printf("l");
		
		if(buf.st_mode & 00400) printf("r");
		else printf("-");
		if(buf.st_mode & 00200) printf("w");
		else printf("-");
		if(buf.st_mode & 00100) printf("x");
		else printf("-");
		if(buf.st_mode & 00040) printf("r");
		else printf("-");
		if(buf.st_mode & 00020) printf("w");
		else printf("-");
		if(buf.st_mode & 00010) printf("x");
		else printf("-");
		if(buf.st_mode & 00004) printf("r");
		else printf("-");
		if(buf.st_mode & 00002) printf("w");
		else printf("-");
		if(buf.st_mode & 00001) printf("x");
		else printf("-");
		
		printf(" %o", (unsigned int)buf.st_nlink);

		printf(" %5d", (int)buf.st_size);

		timeStampToDate((long long int)buf.st_ctime);

		printf(" %s", dent->d_name);

		printf("\n");
	}
}

int chkTotal(){

	struct dirent *dent;
	struct stat buf;
	DIR *dp;
	int sum = 0;
	
	dp = opendir(".");
	
	while (dent = readdir(dp))
	{
		if ((lstat(dent->d_name, &buf)) == 0 && dent->d_name[0] != '.')
			sum = sum + buf.st_blocks;
	}
	
	closedir(dp);
	
	return sum / 2;
}

int main(int argc, char* argv[]){

	if(argc != 1){
		printf("Guide : <Program name>\n");
		exit(1);
	}

	int total = chkTotal();

	printf("total %d\n", total);
	printInfo();

	return 1;
}
