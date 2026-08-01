#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"


int
main(int argc, char *argv[])
{
    const int MEM_CONSUME = PGSIZE;
    int found = 128;
    char str64[512];
    while(found > 0){
        char* start = sbrk(MEM_CONSUME);
        
        memmove(&str64, start,512);
        str64[511] = '\0';
        printf("%s\n", str64);
        if(memcmp("very very secret pw is:", start+8, 23) == 0){
            char theChar = *(start + 32);
            if ((theChar >= 'A' && theChar <= 'Z') || (theChar >= 'a' && theChar <= 'z')){
                printf("INSIDE\n");
                printf("%s\n", start + 32);
                exit(0);
                return 0;
            }          
        }
        
        found--;
    }
    fprintf(2, "Never found");
    exit(1);
    return 0;
}
