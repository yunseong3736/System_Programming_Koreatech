#include <stdio.h>
#include <stdlib.h>

int chkArgc(int obj){
	if(obj<4) return 1;
	else return 0;
}

int main(int argc, char* argv[]){
	if (chkArgc(argc) == 1){
		printf("Please provide <input file name1>, <input file name2> and <output file name>.\n");
		exit(0);
	}
	FILE *a = fopen(argv[1], "rb");
	fseek(a, 0, SEEK_END);
	int aSize = ftell(a);
	fseek(a, 0, SEEK_SET);
	if (a == NULL){
		perror(argv[1]);
		exit(1);
	}
	FILE *b = fopen(argv[2], "rb");
	fseek(b, 0, SEEK_END);
	int bSize = ftell(b);
	fseek(b, 0, SEEK_SET);
	if (b == NULL){
		perror(argv[2]);
		exit(1);
	}
	FILE *outputFile = fopen(argv[3], "wb");
	char buf;
	int chk = 0;
	while(ftell(a) != aSize || ftell(b) != bSize){
		
		if(chk == 0) fread(&buf, sizeof(char), 1, a);
		else fread(&buf, sizeof(char), 1, b);
		chk += 1;
		chk %= 2;

		if( 1<=buf && buf<=9){
			if(chk == 0) fseek(a, buf, SEEK_CUR);
			else fseek(b, buf, SEEK_CUR);
		}
		else {
			fwrite(&buf, sizeof(char), 1, outputFile);
		}
	}

	fclose(a);
	fclose(b);
	fclose(outputFile);

	return 1;
}
