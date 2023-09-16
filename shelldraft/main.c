#include "main.h"

/**
 * main - main program where the magic happens
 * Return: 0 on sucess -1 on errors
*/
int main(void)
{
	int i = 0;
	char *command, **argv = NULL, **path_array;

	path_array = split_path();
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
		if (command_exec(argv, path_array) == -1)
			perror("execution failed");
		string_array_free(argv);
		free(command);
	}
	string_array_free(path_array);
	free(command);
return (0);
}
