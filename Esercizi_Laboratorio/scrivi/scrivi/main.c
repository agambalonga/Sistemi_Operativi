//
//  Scrivere un programma C “scrivi.c” che utilizzando la funzione primitiva “write”, scriva in un file “alfabeto.txt” la seguente stringa di caratteri: “ABCDEFGHILMNOPQRSTUVZ”
//

#include <stdlib.h> /*exit*/
#include <errno.h> /*perror*/
#include <stdio.h>
#include <unistd.h> /*write, close*/
#include <sys/types.h> /*open*/
#include <sys/stat.h> /*open*/
#include <fcntl.h> /*open*/
#include <string.h> /*strlen*/

int main(int argc, const char * argv[]) {
    char *string = "ABCDEFGHILMNOPQRSTUVZ";
    int fd = open("alfabeto.txt", O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);
    
    if(fd == -1) {
        perror("open error");
        exit(-1);
    }
    printf("%d", fd);
    int buf = (int) strlen(string);
    
    if ( write(fd, string, buf) != buf) {
        perror("write error");
        exit(-2);
    }
    
    close(fd);
    printf("Write completed succesfully");
    exit(0);
}
