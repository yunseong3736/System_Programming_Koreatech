#include "Lab5_3.h"
#include <unistd.h>

int main(void){

    myTimer_init(2);

    myTimer_on(0);
    usleep(7000);
    myTimer_off(0);

    myTimer_on(0);
    usleep(8000);
    myTimer_off(0);

    myTimer_on(1);
    usleep(1000);
    myTimer_off(1);

    myTimer_print();

    myTimer_finalize();

    return 0;
}