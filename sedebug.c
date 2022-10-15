#include "types.h"
#include "stat.h"
#include "user.h"


#define PNUM 6
#define PRINT_CYCLE 10000000
#define TOTAL_COUNTER 500000000

void sedbug_func(void){
    int n, pid;
    printf(1,"start sedbug \n");

    for (n = 1; n < PNUM; n++){
        pid = fork();
        if (pid < 0){
            break;
        }
        if (pid == 0){
            weightset(n);
            int start_ticks = uptime();
           
            int counter = 0;
            int first = 1;
            int print_counter = 0;
            int end_ticks;
            while (counter <= TOTAL_COUNTER){
              
                if (print_counter == PRINT_CYCLE){
                    if(first){
                        end_ticks = uptime();
                        int time = (end_ticks - start_ticks) * 10;
                        printf(1, "PID: %d, WEIGHT: %d TIMES: %dms \n", getpid(), n, time);
                        first = 0;
                    }
                    print_counter = 0;
                }
                counter++;
                print_counter++;
            }
            printf(1, "PID: %d is terminated\n", getpid());
            exit();
        }
    }
    
    while (wait() != -1);
    printf(1,"end of sedebug command\n");
}

int main(void){
    sedbug_func();
    exit();
}