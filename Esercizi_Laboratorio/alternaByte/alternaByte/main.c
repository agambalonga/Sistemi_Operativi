//
//  main.c
//  alternaByte
//
//  Created by Alberto Gambalonga on 31/03/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 1

int main(int argc, char * argv[]) {
    int filedes, numread, offset = 0;
    char buffer[BUFFSIZE];
    
    if(argc != 2) {
        printf("Missing parameter argument\n");
        exit(-1);
    }
    
    filedes = open(argv[1], O_RDONLY);
    if(filedes == -1) {
        perror("open error");
        exit(-2);
    }
    
    while((numread = (int)read(filedes, buffer, BUFFSIZE)) > 0) {
        if(write(STDOUT_FILENO, buffer, BUFFSIZE) != numread) {
            perror("write error");
            close(filedes);
            exit(-2);
        }
        offset = offset+2;
        if(lseek(filedes, offset, SEEK_SET) == -1) {
            perror("lseek");
            close(filedes);
            exit(-3);
        }
    }
    
    exit(0);
}
