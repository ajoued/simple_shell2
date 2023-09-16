#include "main.h"

/**
 * search_command_path - search for the command
 * @command: command to be searched for
 * Description: search for the command in the path
 * environment variable
 * Return: path to the command if found
 * NULL if not found
*/
char *search_command_path(char *command, char **directories_array)
{
	char *command_path;
	int i = 0;
	size_t arraysize, commandsize = strlen(command);
	struct stat st;

	if (stat(command, &st) == 0)
	{
		return (command);
	}

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
			return (command_path);
		}
		free(command_path);
		i++;
	}
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
int command_exec(char **argv, char **path_array)
{
	int status, i;
	char *command_path;
	pid_t child_pid, terminated_pid;

	command_path = search_command_path(argv[0], path_array);

	if (command_path != NULL)
	{
		if (command_path != argv[0])
			argv = replace_argv0(argv, command_path);

		printf("Executing: ");
		for (i = 0; argv[i] != NULL; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");

		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
				return (-1);
			exit(0);
		}
		else if (child_pid > 0)
		{
			terminated_pid = waitpid(child_pid, &status, 0);
			if (terminated_pid == child_pid)
			{
				return (0);
			}
		}
		else
			perror("fork failed\n");
	}
	return (-1);
}
