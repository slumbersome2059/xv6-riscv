#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/fcntl.h"
#include "../user/user.h"

void fillOutput(int* indOut, char* strOutput, char* strSoFar, int indSoFar, int allIntegers){
    int val = atoi(strSoFar);
    if(val % 5 == 0 ||val % 6 == 0){
        if(allIntegers != -1 && allIntegers){
            for(int i = *indOut; i < indSoFar+*indOut; i++){
                strOutput[i] = strSoFar[i-*indOut];
            }
            *indOut += indSoFar;
            strOutput[*indOut] = ' ';
            *indOut = *indOut + 1;                
        }
    }
       
}

char* findMult(char* fileName){
    int fd = open(fileName, O_RDONLY);
    if(fd < 0){
        fprintf(2, "Filename is incorrect");
        return 0;
    }else{
        struct stat s;
        fstat(fd, &s);
        fprintf(1, "%d\n", (int)s.size);
        char* strSoFar = malloc(s.size);
        int indSoFar = 0;
        char* strOutput = malloc(s.size);
        int indOut = 0;
        char charRec = '\0';
        int allIntegers = -1;
        int n = read(fd, &charRec, 1);
        while(n != 0){
            if(strchr(" -\r\t\n./,", charRec)){
                
                fillOutput(&indOut, strOutput, strSoFar, indSoFar, allIntegers);
                
                for(int i = 0; i < indSoFar; i++){
                    strSoFar[i] = '\0';
                }
                indSoFar = 0;
                allIntegers = -1;
            }else{
                strSoFar[indSoFar] = charRec;
                indSoFar += 1;
                allIntegers = ((allIntegers || allIntegers == -1) && (atoi(&charRec) || charRec == 48));
            }
            n = read(fd, &charRec, 1);
        }
        fillOutput(&indOut, strOutput, strSoFar, indSoFar, allIntegers);
        return strOutput;
    }
}

int main(int argc, char *argv[]){
    //int fd = open("sixfive.txt", O_CREATE|O_RDWR);
    //char* s = "\n\n 435--232/32sws,sdfew2/024,sdw 0, sdew dw\n53221sw";
    //write(fd, s, strlen(s));
    if(argc >= 2){
        for(int i = 1; i < argc; i++){
            fprintf(1, "%s \n", findMult(argv[i]));    
            
        }
    }else{
        fprintf(2, "Only 1 argument provided");
    }
    return 0;
}