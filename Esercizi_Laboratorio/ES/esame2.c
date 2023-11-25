#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc,char** argv)
{

	if(argc!=3)
	{
		fprintf(stderr,"Bisogna inserire ./<Nome Programma> <Path Directory> <Permessi File>\n");
		exit(-1);
	}
	
	int len = strlen(argv[2]);
	
	DIR *dp;
	struct dirent *dirp;
	struct stat buf;
	char buff[100];
	char mode_buff[100];
	unsigned long mode;
	mode = strtoul(argv[2],NULL,8);
	sprintf(buff,"%o",mode);

	
	if( (dp = opendir(argv[1])) == NULL)
	{
		perror("opendir");
		exit(-1);
	}
	
	while( (dirp = readdir(dp)) != NULL)
	{
		stat(dirp->d_name,&buf);
		
		sprintf(mode_buff,"%o",buf.st_mode);
		
		if(len==4)
		{
			memcpy(mode_buff,&mode_buff[1],4);
			mode_buff[4]='\0';
		}
		if(len==3)
		{
			memcpy(mode_buff,&mode_buff[2],3);
			mode_buff[3]='\0';
		}

		if(strcmp(buff,mode_buff)==0)
		{
			printf("\nNome file: %s\n",dirp->d_name);
			printf("Ultima data di modifica: %s",ctime(&buf.st_mtime));
			printf("Permessi file: %o\n",mode);
		}
				
	}
	
	exit(0);

}
