#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

struct dirent {
  ushort inum;
  char name[14];
};
typedef struct dirent dirent;

char* concat(const char *s1, const char *s2){
    // Idea for concat came from stack overflow but I changed parameters
    // Source - https://stackoverflow.com/a/8465083
    // Posted by David Heffernan, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-07-14, License - CC BY-SA 4.0
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    
    memmove(result, s1, len1);
    memmove(result+len1, s2, len2+1);

    return result;
}


void find(char* name, char* currPath){//change init code to add ./ if start is not / and not .
    int fdDir = open(".", 0);
    struct stat sDir;
    if(fstat(fdDir, &sDir) == -1){
        printf("Problem with file status");
        return;
    }
    dirent* entries = malloc(sDir.size);
    int dirSize = sDir.size;
    read(fdDir, entries, sDir.size);//how does sDir.size change????? when read
    int numEntries = (((int)dirSize)/((int)sizeof(dirent)));
    int fd;
    struct stat s;
    
    for(int i = 0; i < numEntries; i++){
        if((entries+i)->name[0] != '\0'){
            char* eName = (entries[i]).name;
            char* p1 = concat(currPath, eName);
            if(strcmp(name, eName) == 0){
                printf("%s\n", p1);
                //char* fmt = startPoint[strlen(startPoint) - 1] != '/' ?  "%s/%s\n" : "%s%s\n";
                //printf(fmt, startPoint, name);
            }
            fd = open(eName, 0);
            if(fd < 0){
                continue;
            }
            if(fstat(fd, &s) < 0){
                continue;
            }
            char* p2 = concat(p1, "/");
            if(((int)s.type) == 1 && (strcmp(eName, ".") != 0) && (strcmp(eName, "..") != 0 )){
                printf("%s \n", eName);
                if(chdir(eName) != -1){
                    find(name, p2);
                    chdir("..");    
                }
            }
            close(fd);
            free(p2);
            free(p1);
        }
    }
    close(fdDir);
    free(entries);
}

char* checkInitPath(char* path){//need to free returned pointer
    char* p1;
    if((*path) == '.'){
        if(strlen(path) == 1){
            return concat("", "./");
        }else{
            p1 = concat("", path);
        }
    }else if((*path) == '/'){
        p1 = concat("", path);
    }else{
        p1 = concat("./", path);
    }
    int p1Len = strlen(p1);
    char* p2;
    if(p1[p1Len - 1] != '/'){
        p2 = concat(p1, "/");
        return p2;
    }
    return p1;
}



int
main(int argc, char *argv[])
{
    if(argc == 2){
        find(argv[1], "./");
    }else{
        char* p = checkInitPath(argv[1]);
        if(chdir(p) != -1){
            find(argv[2], p);
            free(p);
            exit(0);
        }
        fprintf(2, "Problem with starting point input");
        free(p);
        exit(0);
    }
    
    return 0;
}