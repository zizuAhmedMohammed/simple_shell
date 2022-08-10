#include "shell.h"

/**
 * _realloc - reallocs a mem block
 * @ptr: ptr to old mem
 * @old_size: # of bytes allocated for sp in ptr
 * @new_size: # of bytes in new mem block
 * Return: new ptr
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	for (i = 0; i < new_size && i < old_size; i++)
		new[i] = ((char *) ptr)[i];
	free(ptr);
	return (new);
}

/**
 * create_env - copies environ (extern var) to my_environ
 * Return: copy of environ
 */

char **create_env(void)
{
	char **my_environ;
	int i = 0, len1 = 0;

	while (environ[len1])
		len1++;
	my_environ = malloc((len1 + 1) * sizeof(char *));
	if (my_environ == NULL)
	{
		print_error("Error: mem allocation\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < len1; i++)
	{
		my_environ[i] = malloc((_strlen(environ[i]) + 1) * sizeof(char));
		if (my_environ[i] == NULL)
		{
			for ( ; i >= 0; i--)
				free(my_environ[i]);
			free(my_environ);
			return (NULL);
		}
		my_environ[i] = _strcpy(my_environ[i], environ[i]);
	}
	my_environ[i] = NULL;
	return (my_environ);
}

/**
 * free_env - frees environ copy
 */

void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * copy_path - copies PATH values to buffer
 * Return: ptr to copy of PATH values
 */

char *copy_path(void)
{
	char *path_val;

	path_val = malloc(_strlen(_getenv("PATH")) * 2);
	if (path_val == NULL)
	{
		path_val = "";
		return (path_val);
	}
	path_val = _strcpy(path_val, _getenv("PATH"));
	return (path_val);
}

/**
 * check_comment - checks user input for '#' symbol
 * @line: ptr to address of user input string
 */

void check_comment(char **line)
{
	int i;

	for (i = 0; (*line)[i]; i++)
	{
		if ((*line)[i] == ' ' && (*line)[i + 1] == '#')
		{
			(*line)[i] = '\0';
			break;
		}
	}
}
