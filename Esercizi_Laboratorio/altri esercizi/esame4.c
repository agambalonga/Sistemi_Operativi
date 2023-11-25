#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		fprintf(stderr,"Bisogna immettere ./<Nome Programma> <Nome file>\n");
		exit(-1);
	}
	
	char *name_file = argv[1];
	
	struct stat buf;
	
	stat(name_file,&buf);
	
	printf("UID file: %d, Grandezza file: %d, Permessi file: %o\n",buf.st_uid,buf.st_size,buf.st_mode);
	
	exit(0);
	

}
