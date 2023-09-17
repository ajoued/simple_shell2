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
	char *command, **argv = NULL, **path_array;

	ac = ac;
	path_array = split_path();
	while (1)
	{
		command = prompt();
		argv = split_command(command);
		free(command);
		cmd_count++;
		command_exec(argv, path_array, av[0], cmd_count);
		string_array_free(argv);
	}
	string_array_free(path_array);
	free(command);
	return (0);
}
