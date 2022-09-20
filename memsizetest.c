#include "types.h"
#include "stat.h"
#include "user.h"
#define SIZE 2048
int main(int argc, char *argv[]){
    int msize = memsize();
    printf(1, "The Process is using %dB\n", msize);
    char *tmp = (char *)malloc(SIZE * sizeof(char));
    
    printf(1, "Allocationg more memory \n");
    msize = memsize();
    printf(1, "The Process is using %dB\n", msize);

    free(tmp);
    printf(1, "Freeing memory \n");
    msize = memsize();
    printf(1, "The Process is using %dB\n", msize);
    exit();

}