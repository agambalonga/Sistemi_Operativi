//
//  main.c
//  fork
//
//  Created by Alberto Gambalonga on 19/04/23.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    int glob = 4;
    int pid = 1;
    fork();
    glob++;
    if(!fork()) {
        pid = fork();
        glob=glob*2;
    }
    
    if(!pid) {
        fork();
        glob = glob-2;
    }
    glob++;
    printf("Processo PID=%d , PPID=%d -> glob=%d\n",getpid(),getppid(),glob);
    
    return 0;
}
