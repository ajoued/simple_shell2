#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * dierctory_count - counts how many dierctories are in path variable
 * @path: path to be treated
 * Return: number of dierctories in the path
*/
int dierctory_count(char *path)
{
int count, i = 0;


	if (path == NULL)
		return (0);
	count = 1;
	while (path[i] != '\0')
	{
		if(path[i] == ':')
			count++;
		i++;
	}

	return (count);
}

/**
 * split_path - splits path dierctories
 * @path: path to be treated
 * Return: an array of dierctories
 * 
*/
char **split_path(char *path, int count)
{
	char **array = NULL, *token;
	int i = 0;

	if (path == NULL)
		return (NULL);
	array = realloc(array, sizeof(char *) * (count + 1));
	token = strtok(path, ":");
	while(token != NULL)
	{
		array[i] = strdup(token);
		token = strtok(NULL, ":");
		i++;
	}
	array[i] = NULL;
	return (array);
}

/**
 * search_path - search for the command
 * @array: array of dierctories in PATH
 * @command: command to be searched for
 * @num: number of directories in the array
 * Return: path to the command if found
 * NULL if not found
*/
char *search_path(char **array, char *command, int num)
{
	int i = 0;
	char *path;
	size_t arraysize, commandsize = strlen(command);
	struct stat st;

	for (i = 0; i < num; i++)
	{
		arraysize = strlen(array[i]); 
		path = malloc(sizeof(char *) * arraysize + sizeof(char *) * commandsize + 2);
		strcpy(path, array[i]);
		strcat(path, "/");
		putchar(path[arraysize + 1]);
		strcat (path, command);
		if (stat(path, &st) == 0)
		{
			printf("command path is %s\n", path);
			return (path);
		}
		free(path);
	}
	printf("command %s: NOT FOUND\n", command);
	return (NULL);
}

/**
 * main - main programm
 * @ac: arguments count
 * @av: arguments array
 * Return: always 0
*/
int main (void)
{
    char *path, **array, *command = "hello", *full_path;
	int count, i;

	path = getenv("PATH");
	count = dierctory_count(path);
	printf("%d\n", count);
	array = split_path(path, count);
	array = array;
	for (i = 0; i < count ; i++)
	{
		printf("%s\n", array[i]);
	}
	full_path = search_path(array, command, count);
	if (full_path != NULL)
	{
		
	}
	for (i = 0; i < count ; i++)
	{
		free(array[i]);
	}
	free(array);
	return (0);
}