#include "main.h"

/**
 * search_command_path - search for the command
 * @command: command to be searched for
 * Description: search for the command in the path
 * environment variable
 * Return: path to the command if found
 * NULL if not found
*/
char *search_command_path(char *command)
{
	char **directories_array, *command_path;
	int i = 0;
	size_t arraysize, commandsize = strlen(command);
	struct stat st;

	if (stat(command, &st) == 0)
	{
		return (command);
	}

	directories_array = split_path();

	while (directories_array[i] != NULL)
	{
		arraysize = strlen(directories_array[i]);
		command_path = malloc(sizeof(char *) * arraysize +
		sizeof(char *) * commandsize + 2);
		strcpy(command_path, directories_array[i]);
		strcat(command_path, "/");
		strcat(command_path, command);
		if (stat(command_path, &st) == 0)
		{
			printf("command path is %s\n", command_path);
			string_array_free(directories_array);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	string_array_free(directories_array);
	printf("command %s: NOT FOUND\n", command);
	return (NULL);

}


/**
 * replace_argv0 - replace the command in argv[0]
 * with the full command path
 * @argv: array of the command and its arguments
 * @full_path: full path of the command
 * Return: the array of the full command path with its arguments
*/
char **replace_argv0(char **argv, char *full_path)
{
	free(argv[0]);
	argv[0] = full_path;
	return (argv);
}

/**
 * command_exec - executes the command in a child process
 * @argv: array of the command and and it's arguments
 * Return: 0 on success -1 on error
*/
void command_exec(char **argv)
{
	int status;
	char *command_path;
	pid_t child_pid; /*, terminated_pid;*/

	command_path = search_command_path(argv[0]);

	if (command_path != NULL)
	{
		if (command_path != argv[0])
			argv = replace_argv0(argv, command_path);

		child_pid = fork();
		if (child_pid == 0)
		{
			execve(argv[0], argv, NULL);
		}
		else if (child_pid > 0)
		{
			waitpid(child_pid, &status, 0);
		}
		else
			perror("fork failed\n");
	}
	string_array_free(argv);
}
