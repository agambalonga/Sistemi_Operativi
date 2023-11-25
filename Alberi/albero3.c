#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 5;

int main ()
{
	pid_t pid;
	int i;
	for (i = 1; i < glob; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob - 1;
		}
	}

	printf ("Process %d, glob = %d, i = %d\n", getpid(), glob, i);
	exit (0);
}
