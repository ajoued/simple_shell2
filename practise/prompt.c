#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - main prompt
 * Return: 0 if success nonzero if it fails
*/
int main(void)
{
	int i = 0;
	char *command = NULL, *token = NULL, **array = NULL;
	size_t size = 0;
	ssize_t size2; 
	while (1)
	{
		printf("$ ");
		command = NULL;
		size2 = getline(&command, &size, stdin);
		command[size2 - 1] = '\0';
		if (feof(stdin) != 0)
			break;
		if (strncmp(command, "exit", 4) == 0 || strncmp(command, "exit ", 5) == 0)
			break;
		i = 0;
		token = NULL;
		array = NULL;
		token = strtok(command, " ");
		
		while(token != NULL)
		{
			array = realloc(array, sizeof(char *) * (i + 1));
			array[i] = strdup(token);
			token = strtok(NULL, " ");
			i++;
		}
		array = realloc(array, sizeof(char *) * (i + 1));
		array[i] = NULL;
		i = 0;
		while (array[i] != NULL)
		{
			printf("%s\n", array[i]);
			free(array[i]);
			i++;
		}
		free(array);
		free(command);
	}
	free(command);
	return (0);
}
