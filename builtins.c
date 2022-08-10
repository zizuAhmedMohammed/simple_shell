#include "shell.h"

/**
 * my_exit - exits shell
 * @args: ptr to str of args
 * @prgm: prgm name for print error
 * @count: count user input for print error
 * Return: 2 if exit receives invalid arg
 */
int my_exit(char **args, char *prgm, int count)
{
	int num = 0, i = 0;
	(void) prgm, (void) count;

	if (args == NULL || args[1] == NULL)
		exit(0);
	while (args[1][i])
	{
		if (!(args[1][i] >= '0' && args[1][i] <= '9'))
			break;
		num *= 10;
		num += args[1][i] - '0';
		i++;
	}
	if (args[1][i] == '\0')
		exit(num);
	print_error("%s: %d: exit: Illegal number: %s\n", prgm, count, args[1]);
	return (2);
}

/**
 * print_env - prints environment key-value pairs
 * @args: ptr to str of args
 * @prgm: prgm name for print error
 * @count: count user input for print error
 * Return: 0 on success, 1 otherwise
 */
int print_env(char **args, char *prgm, int count)
{
	size_t i = 0;
	(void) prgm, (void) count;

	if (args == NULL || args[0] == NULL)
		exit(EXIT_FAILURE);
	for ( ; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * _unsetenv - removes a var from user environment
 * @args: ptr to ptr to args
 * @prgm: prgm name for print error
 * @count: count user input for print error
 * Return: -1 if var not found, 0 on success
 */
int _unsetenv(char **args, char *prgm, int count)
{
	int i = get_index(args[1]);
	(void) prgm, (void) count;

	if (args == NULL || args[1] == NULL || i == -1 || !_strlen(args[1]))
		return (-1);
	free(environ[i]);
	while (environ[i])
	{
		environ[i] = environ[i + 1];
		i++;
	}
	return (0);
}
/**
 * my_cd - changes directory
 * @args: ptr to str of args
 * @prgm: prgm name for print error
 * @count: count user input for print error
 * Return: 0 success, 2 on error
 */
int my_cd(char **args, char *prgm, int count)
{
	if (args[1] == NULL)
	{
		change_pwd("OLDPWD", prgm, count);
		chdir(_getenv("HOME"));
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		chdir(_getenv("OLDPWD"));
		change_oldpwd(prgm, count);
	}
	else
	{
		change_oldpwd(prgm, count);
		if (chdir(args[1]) == -1)
		{
			print_error("%s: %d: cd: can't cd to %s\n", prgm, count, args[1]);
			return (2);
		}
	}
	change_pwd("PWD", prgm, count);
	return (0);
}
/**
 * _setenv - sets new environ var, or updates existing
 * @args: ptr to ptr to args
 * @prgm: prgm name for print error
 * @count: count user input for print error
 * Return: 0
 */
int _setenv(char **args, char *prgm, int count)
{
	char *buffer;
	int i = get_index(args[1]), n = sizeof(char *);
	size_t len1 = 0;
	(void) prgm, (void) count;

	if (args[1] && args[2] && args[3])
		return (-1);
	if (args[1] == NULL)
		return (print_env(args, prgm, count));
	while (environ[len1])
		len1++;
	buffer = malloc((_strlen(args[1]) + _strlen(args[2]) + 2));
	if (buffer == NULL)
		exit(EXIT_FAILURE);
	_strcpy(buffer, args[1]);
	_strcat(buffer, "=");
	if (args[2])
		_strcat(buffer, args[2]);
	else
		_strcat(buffer, " ");
	if (i >= 0)
	{
		free(environ[i]);
		environ[i] = buffer;
	}
	else
	{
		free(environ[len1]);
		environ = _realloc(environ, (len1 + 1) * n, (len1 + 2) * n);
		environ[len1] = buffer;
		environ[len1 + 1] = NULL;
	}
	return (0);
}
