#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * main - executes the command ls -l /tmp in 5 different child processes
 * Return: 0 always
*/
int main(void)
{
	int status, i = 0;
	pid_t child_pid, terminated_pid, cpid;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	while (i < 5)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			cpid = getpid();
			printf("current pid is: %u\n", cpid);
			execve(argv[0], argv, NULL);
	    	exit(0);
		}
		else if (child_pid > 0)
		{
			terminated_pid = waitpid(child_pid, &status, 0);
			if (terminated_pid == child_pid)
			{
				i++;
			}
		}
		else
			perror("fork failed\n");
	}
	return (0);
}