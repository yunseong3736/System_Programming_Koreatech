//대문자가 좋아요
#include <stdio.h>
#include <stdlib.h>

int isAlphabet(char obj){
	if ('a' <= obj && obj <= 'z') return 1;
	else return 0;
}

int chkArgc(int obj){
	if(obj<3) return 1;
	else return 0;
}

int main(int argc, char* argv[]){

	if (chkArgc(argc) == 1){
		printf("Please provide <input file name> and <output file name>.\n");
		exit(0);
	}

	FILE *inputFile = fopen(argv[1], "r");
	if (inputFile == NULL){
		perror(argv[1]);
		exit(1);
	}

	FILE *outputFile = fopen(argv[2], "w");
	int c;

	while ( (c = fgetc(inputFile)) != EOF) {
		if (isAlphabet((char)c) == 1) fputc(c-'a'+'A', outputFile);
		else fputc(c, outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);

	return 1;
}
