//
//  main.c
//  invertiByte
//
//  Created by Alberto Gambalonga on 29/03/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    if(argc != 2) {
        printf("Missing fileName argument\n");
        exit(-1);
    }
    
    int fdSource = open(argv[1], O_RDONLY);
    char c;
    
    if(fdSource == -1) {
        perror("open error");
        exit(-2);
    }
    
    off_t off = lseek(fdSource, 0, SEEK_END);
    
    for(int i = (int)off; i>=0; i--) {
        
        if((read(fdSource, &c, 1))==1) {
            if((write(STDOUT_FILENO, &c, 1)) == -1 ){
                perror("write");
                exit(-3);
            }
        }
        
        lseek(fdSource, i, SEEK_SET);
    }
    
    return 0;
}
