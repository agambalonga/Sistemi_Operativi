//
//  main.c
//  ls
//
//  Created by Alberto Gambalonga on 21/03/23.
//
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    DIR *dir;
    struct dirent *dirp;
    
    if(argc != 2) {
        printf("Missing dir_name argument\n");
        exit(-1);
    }
    
    if((dir = opendir(argv[1])) == NULL) {
        perror("opendir");
        exit(-2);
    }
    
    while((dirp = readdir(dir)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    
    return 0;
}
