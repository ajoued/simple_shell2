#include <stdio.h>
#include <stdlib.h>

/**
* main - prints all the arguments without using ac
* ac; arguments count
* av: arguments array
* Return: 0 (always success)
*/
int main(int ac, char **av)
{
	int i = 1;
	
	while(av[i] != NULL)
	{
		printf("%s\n", av[i]);
		i++;
	}
return (0);
}