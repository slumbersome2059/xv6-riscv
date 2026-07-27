#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p = 0;
    if(argc <= 3){
        fprintf(2, "Not enough arguments for sandbox\n");
        exit(-1);
    }else{
        int pid = fork();
        if(pid > 0){
            wait(0);
        }else if(pid == 0){
            if(interpose(atoi(argv[1]), argv[2]) < 0){
                fprintf(2, "Problem with interpose");
                exit(-1);
            }
            if(exec(argv[3], argv + 3)<0){
                fprintf(2, "Problem with exec %d\n", p++);
                exit(-1);
            }
            exit(0);
        }else{
            fprintf(2, "Fork error\n");
            exit(0);
        }
    }
    exit(0);
    return 0;
}