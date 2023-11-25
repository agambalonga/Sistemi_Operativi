#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc,char** argv)
{

	if(argc!=3)
	{
		fprintf(stderr,"Bisogna immettere ./<Nome Programma> <Nome Directory> <Permessi>\n");
		exit(-1);
	}

	char *dir_path = argv[1];
	mode_t perm_mode = strtol(argv[2],NULL,8);
	
	DIR *dir = opendir(dir_path);
	
	struct dirent *entry;
	
	while( (entry =readdir(dir)) != NULL)
	{
		if(entry->d_type==DT_REG)
		{
			char file_path[1000];
			snprintf(file_path,strlen(file_path),"%s%s",dir_path,entry->d_name);
			
			struct stat file_stat;
			
			stat(file_path,&file_stat);
			
			if((file_stat.st_mode & 0777) == perm_mode) 
			{
			
				char *mod_time = ctime(&file_stat.st_mtime);
				mod_time[strlen(mod_time)-1] = '\0';
				
				printf("%s %o %s\n",entry->d_name,file_stat.st_mode & 0777,mod_time);
			}
		
		}
	
	}
	
	exit(0);



}


