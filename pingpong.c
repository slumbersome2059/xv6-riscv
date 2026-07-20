#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(void){
    printf("INSIDE");
    int pipe1[2] = {0, 0}; 
    int pipe2[2] = {0, 0}; 
    
    pipe(pipe1);
    pipe(pipe2);
    int pid = fork();
    printf("INSIDE\n");
    int count = 0;
    if(pid > 0){//write into pipe1, read from pipe2
        char i[10] = "123456789\0";
        char writeVal[10] = "123456789\0";
        close(pipe1[0]);
        close(pipe2[1]);
        printf("INSIDE1\n");
        write(pipe1[1], writeVal, 10);  
        while(read(pipe2[0], writeVal, 10) != 0 && count < 5000){
            //printf("%c\n", *writeVal);
            write(pipe1[1], writeVal, 10);
            count++;
        }
    }else if(pid == 0){
        printf("INSIDE2\n");
        char writeVal[10] = {};
        close(pipe1[1]);
        close(pipe2[0]);
        while(read(pipe1[0], writeVal, 10) != 0 && count < 5000){
            write(pipe2[1], writeVal, 10);
            count++;
        }
        
        exit(0);
    }else{
        fprintf(2, "Problem with fork");
    }
    exit(0);
    return 0;
};