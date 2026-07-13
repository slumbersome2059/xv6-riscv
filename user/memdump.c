#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int memdump(char *fmt, char *data){
    int dataInd = 0;
    int initLengthFmt = strlen(fmt); 
    for(int i = 0; i < initLengthFmt; i++){//check that length received
        switch(fmt[i]){
            case 'i':{
                char dec32[4];
                memmove(&dec32, data + dataInd,4);
                int* s = (int*)(dec32);
                printf("%d\n", *s);
                dataInd += 4;
                break;
            };
            case 'p':{
                char dec64[8];
                memmove(&dec64, data + dataInd,8);
                long* l = (long*)(dec64);
                printf("%lx\n", *l);
                dataInd += 8;
                break;
            };
            case 'h':{
                char dec16[2];
                memmove(&dec16, data + dataInd,2);
                short* c = (short*)(dec16);
                printf("%d\n", *c);//%hd does not work
                dataInd += 2;
                break;
            };
            case 'c':{
                printf("%c\n", data[dataInd]);
                dataInd += 1;
                break;
            };
            case 's':{
                char str64[8];
                memmove(&str64, data + dataInd,8);
                printf("%s\n", str64);
                dataInd += 8;
                break;
            };
            case 'S':{
                printf("%s\n", data+dataInd);
                break;
            };
            default:{
                return -1;//invalid fmt string
            }
        }
    }
    return 0;
}
int
main(int argc, char *argv[])
{
    if(argc == 1){
        printf("Example 1:\n");
        int a[2] = { 61810, 2025 };
        memdump("ii", (char*) a);
        
        printf("Example 2:\n");
        memdump("S", "a string");
        
        printf("Example 3:\n");
        char *s = "another";
        memdump("s", s);
        
        struct sss {
        char *ptr;
        int num1;
        short num2;
        char byte;
        char bytes[8];
        } example;
        
        example.ptr = "hello";
        example.num1 = 1819438967;
        example.num2 = 100;
        example.byte = 'z';
        strcpy(example.bytes, "xyzzy");
        
        printf("Example 4:\n");
        memdump("pihcS", (char*) &example);
        
    }else{
        char buf[512];
        read(0, buf, 512);
        memdump(argv[1], buf);
    }
    
}