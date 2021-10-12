#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char *output = "[%m월 %d일 %a %R %p]";
char *timeZone[] = {"GMT", "KST", "JST", "CST", "MST", "BRT", "CEST", "EAT", "AEST"};
int timeDifference[] = {0, 32400, 32400, 28800, -25200, -10800, 7200, 10800, 36000};

int getTimeDifference(char *obj){
    if(obj[0] == 'G' && obj[1] == 'M') return 0;
    else if(obj[0] == 'K' && obj[1] == 'S') return 1;
    else if(obj[0] == 'J' && obj[1] == 'S') return 2;
    else if(obj[0] == 'C' && obj[1] == 'S') return 3;
    else if(obj[0] == 'M' && obj[1] == 'S') return 4;
    else if(obj[0] == 'B' && obj[1] == 'R') return 5;
    else if(obj[0] == 'C' && obj[1] == 'E' && obj[2] == 'S') return 6;
    else if(obj[0] == 'E' && obj[1] == 'A') return 7;
    else if(obj[0] == 'A' && obj[1] == 'E' && obj[2] == 'S') return 8;
    else return -1;
}

int main(int argc, char* argv[]){
    if (argc == 1) {
        printf("Please provide <Time Zone Name>\n");
        exit(1);
    }
    
    int idx = getTimeDifference(argv[1]);
    if (idx == -1) {
        printf("Please check <Time Zone Name>\nTime Zone Name List : GMT, KST, JST, CST, MST, BRT, CEST, EAT, AEST\n");
        exit(1);
    }
    int timeDiff = timeDifference[idx];

    time_t t;
    time(&t);

    char buf[255];
    struct tm *time1, *time2;
    
    time_t t1 = t + 32400;
    time1 = gmtime(&t1);
    strftime(buf, sizeof(buf), output, time1);
    printf("KST : %s\n", buf);
    
    time_t t2 = t + timeDiff;
    time2 = gmtime(&t2);
    strftime(buf, sizeof(buf), output, time2);
    printf("%s : %s\n", timeZone[idx], buf);

    return 1;
}