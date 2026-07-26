#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(2, "No arguments provided\n");
    }else{
        int sleepTime = 0;
        for(int i = 1; i < argc;i++){//look at how this starts from 1, first arg is sleep
            sleepTime += atoi(argv[i]);
        }
        if(pause(sleepTime)!= 0){
            fprintf(2, "Error in pause sys-call");
        }        
    }
    return 0;
}