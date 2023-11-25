#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char** argv)
{

	if(argc!=4)
	{
		fprintf(stderr,"Bisogna immettere ./<Nome Programma> <Nome Directory> <Dimensione Minima> <Dimensione Massima>\n");
		exit(-1);
	}
	
	int min = atoi(argv[2]);
	int max = atoi(argv[3]);
	char *dir_path = argv[1];
	
	DIR *dir;
	struct dirent *directory;
	struct stat buf;
	
	if( (dir = opendir(dir_path)) < 0)
	{
		perror("opendir");
		exit(-1);
	}
	
	while( (directory = readdir(dir)) != NULL)
	{
	
		stat(directory->d_name,&buf);
		
		if(buf.st_size>=min && buf.st_size<=max)
			printf("Nome file: %s\n",directory->d_name);
	
	}
	
	exit(0);
	


}
