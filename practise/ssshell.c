#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/**
 * prompt - prints the prompt and gets the command
 * Return: a pointer to the string of the command
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
 * split_command - splits command into little parts and store it in an array
 * @command: command to be treated
 * Return: pointer to the little parts array
*/
char **split_command(char *command)
{
	char *token = NULL, **array = NULL;
	int i = 0;

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

/**
 * command_exec - exutes a commande in a child process
 * @argv: array of the command and arguments
 * Return: 0 on success -1 on error
*/
void command_exec(char **argv)
{
	int status;
	struct stat st;
	pid_t child_pid, terminated_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (stat(argv[0], &st) == 0)
		{
			execve(argv[0], argv, NULL);
		}
		else
			printf("command not found\n");
		exit(0);
	}
	else if (child_pid > 0)
	{
		terminated_pid = waitpid(child_pid, &status, 0);
		if (terminated_pid == child_pid)
		{
		}
	}
	else if (child_pid < 0)
	{
		perror("fork failed\n");
	}
}

/**
 * main - main shell
 * Return: when exiting with no errors (0)
*/
int main(void)
{
	int i = 0;
	char *command, **argv = NULL;

	while (1)
	{
		command = prompt();
		argv = split_command(command);
		command_exec(argv);
		i = 0;
		while (argv[i] != NULL)
		{
			printf("%s\n", argv[i]);
			free(argv[i]);
			i++;
		}
		free(argv);
		free(command);
	}
	free(command);
	return (0);
}
