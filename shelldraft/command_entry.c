#include "main.h"

/**
 * prompt - displays the shell
 * and allows the user to enter the command
 * Return: a pointer to the command string
*/
char *prompt(void)
{
	char *command = NULL;
	size_t size = 0;
	ssize_t size2;

	printf("$ ");
	size2 = getline(&command, &size, stdin);
	command[size2 - 1] = '\0';
	if (feof(stdin) != 0)
	{
		free(command);
		exit(0);
	}
	if (strncmp(command, "exit", 4) == 0 || strncmp(command, "exit ", 5) == 0)
	{
		free(command);
		exit(0);
	}
	return (command);
}

/**
 * split_command - splits the command parts and stores them
 * in an array of strings
 * @command: command to be treated
 * Return: a pointer to the array of strings
*/
char **split_command(char *command)
{
	char *token = NULL, **array = NULL;
	int i = 0;

	command = command;
	token = strtok(command, " ");
	while (token != NULL)
	{
		array = realloc(array, sizeof(char *) * (i + 1));
		array[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;
	}
	array = realloc(array, sizeof(char *) * (i + 1));
	array[i] = NULL;

return (array);
}
