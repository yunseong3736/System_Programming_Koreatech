#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE 10

int n;
struct timeval* on;
struct timeval* off;
double *timer;

int myTimer_init (int numTimers){
    n = numTimers;
    if(n > SIZE){
        printf("Too many timers! (MAX : 10)\n");
        return -1; //error
    }

    timer = (double*)malloc(sizeof(double)*n);
    on = (struct timeval*)malloc(sizeof(struct timeval)*n);
    off = (struct timeval*)malloc(sizeof(struct timeval)*n);

    return 0;
}

int myTimer_finalize(void){
    free(timer);
    free(on);
    free(off);

    return 0;
}

int myTimer_on(int timerID){
    return gettimeofday(&on[timerID], NULL);
}

int myTimer_off(int timerID){
    if (gettimeofday(&off[timerID], NULL) == -1){
        return -1;
    }

    timer[timerID] += (double)((off[timerID].tv_sec) - (on[timerID].tv_sec)) * 1000.0;
    timer[timerID] += (double)((off[timerID].tv_usec) - (on[timerID].tv_usec)) / 1000.0;

    return 0;
}

int myTimer_print(void){
    for (int i = 0; i < n; i++){
        printf("Time %d : %.2f ms\n", i, timer[i]);
    }

    return 0;
}