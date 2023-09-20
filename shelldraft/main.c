#include "main.h"

/**
 * main - main program where the magic happens
 * @ac: arguments count
 * @av: program name and arguments array
 * Return: 0 on sucess -1 on errors
*/

int main(int ac, char **av)
{
	int cmd_count = 0;
	char *command = NULL, **argv = NULL, **path_array;

	ac = ac;
	path_array = split_path();
	while (1)
	{
		command = NULL;
		command = prompt();
		if (command != NULL && command[0] != '\0')
		{
			argv = split_command(command);
			if (strcmp(argv[0], "exit") == 0)
			{
				free(command);
				string_array_free(path_array);
				shell_exit(argv, av[0], cmd_count);
			}
			else if (strcmp(argv[0], "env") == 0)
			{
				ptrenv();
			}
			free(command);
			cmd_count++;
			command_exec(argv, path_array, av[0], cmd_count);
			string_array_free(argv);
		}
		else
			free(command);
	}
	string_array_free(path_array);
	free(command);
	return (0);
}
