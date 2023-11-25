#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
    DIR* dp;
    struct dirent* dir;
    struct stat fs;


    dp = opendir(argv[1]);
    while((dir = readdir(dp)) != NULL) {
        int r = stat(dir->d_name, &fs);

        if(r == -1) {
            perror("stat");
            return -1;
        } else {
            if(S_ISREG(fs.st_mode)) {
                if((fs.st_mode & S_IRUSR) && (fs.st_mode & S_IWUSR) && (fs.st_mode & S_IWOTH) && (fs.st_mode & S_IROTH)) {
                    printf("File %s is regular, size = %d\n", dir->d_name, fs.st_size);
                }
            }

        }
    }

    closedir(dp);

    return 0;
}