#include "main.h"

/**
 * split_path - splits path dierctories
 * Return: an array of dierctories
*/
char **split_path(void)
{
	char **directories_array = NULL, *token, *path_string;
	int i = 0, count;

	path_string = getenv("PATH");
	if (path_string == NULL)
		return (NULL);
	count = dierctory_count(path_string);
	directories_array = realloc(directories_array, sizeof(char *) * (count + 1));
	token = strtok(path_string, ":");
	while (token != NULL)
	{
		directories_array[i] = strdup(token);
		token = strtok(NULL, ":");
		i++;
	}
	directories_array[i] = NULL;
	return (directories_array);
}

/**
 * dierctory_count - counts how many dierctories are in path variable
 * @path_string: path to be treated
 * Return: number of dierctories in the path
*/
int dierctory_count(char *path_string)
{
int count, i = 0;


	if (path_string == NULL)
		return (0);
	count = 1;
	while (path_string[i] != '\0')
	{
		if (path_string[i] == ':')
			count++;
		i++;
	}

	return (count);
}

/**
 * string_array_free - frees an array of strings
 * @array: array to be treated
 * Return:nothing
*/
void string_array_free(char **array)
{
	int i = 0;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
