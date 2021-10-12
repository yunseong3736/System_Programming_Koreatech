#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int chkString(char *a, char *b){
    int i = 0;
    while (a[i] && b[i]){
        if (a[i] != b[i]) return 0;
        i++;
    }
    if (a[i] || b[i]) return 0;
    return 1;
}

int main(int argc, char* argv[]){

    if (argc != 3){
        printf("Guide <program name> <student number> <output file name>\n");
        exit(1);
    }

    FILE *inputFile = fopen("/home/professor/grade.db", "r");
    if (inputFile == NULL){
        printf("grade.db does not exist!!\nPlease check /home/professor/\n");
        exit(1);
    }

    char studentNumber[256], grade[3];
    int idx, gradeidx = 0, c;
    while(1){
        
        //Read studentNumber from grade.db and compare with argv[1] (target studentNumber)
        idx = 0;
        while ( (c = fgetc(inputFile)) != ' ' && c != EOF){
            studentNumber[idx++] = (char)c;
        }
        if (idx == 0) break;
        studentNumber[idx] = '\0';
        
        //If found target studentNumber, read & memorize grade
        if (chkString(studentNumber, argv[1]) == 1){
            while ( (c = fgetc(inputFile)) != '\n' ){
                grade[gradeidx++] = (char)c;
            }
        }
        //If not, pass
        else {
            while ( (c = fgetc(inputFile)) != '\n' ){
                continue;
            }
        }
    }

    if (gradeidx == 0){
        printf("Please check Studen Number!!\n");
        exit(1);
    }

    uid_t uid, euid;
    uid = getuid();
    euid = geteuid();

    printf("uid = %d, euid = %d\n", (int)uid, (int)euid);

    printf("my grade = %s\n", grade);

    seteuid(uid);
    euid = geteuid();
    printf("uid = %d, euid = %d\n", (int)uid, (int)euid);
    
    printf("Write the grade to %s\n", argv[2]);
    FILE *outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%s\n", grade);
    
    return 1;
}