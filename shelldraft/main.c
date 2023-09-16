#include "main.h"

/**
 * main - main program where the magic happens
 * Return: 0 on sucess -1 on errors
*/
int main(void)
{
	int i = 0;
	char *command, **argv = NULL;

	while (1)
	{
		command = prompt();
		argv = split_command(command);
		i = 0;
		while (argv[i] != NULL)
		{
			printf("%s\n", argv[i]);
			i++;
		}
		command_exec(argv);
		free(command);
	}
	free(command);
return (0);
}
