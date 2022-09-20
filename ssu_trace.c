#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[]){
    trace(atoi(argv[1]));
    char **command = (char **)malloc((argc - 1) * sizeof(char*));
    for (int i = 0; i <= argc - 2; i++){
        command[i] = argv[i + 2];
        // printf(1, "%d : %s\n", i, command[i]);
    }
    exec(argv[2], command);
    exit();
}