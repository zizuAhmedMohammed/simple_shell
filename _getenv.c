#include "header.h"

/**
 * get_index - gets index of env var in environ
 * @name: env var key to search for
 * Return: index
 */
int get_index(const char *name)
{
	int i, j;

	if (name == NULL)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		if (name[0] == environ[i][0])
		{
			for (j = 0; (name[j] == environ[i][j]) && name[j]; j++)
				;
			if (!name[j])
				break;
		}
	}
	if (environ[i] == NULL)
		return (-1);
	return (i);
}

/**
 * _getenv - gets ptr to values of an env var
 * @name: env var key to search for
 * Return: ptr to value of the env var
 */
char *_getenv(const char *name)
{
	int index = get_index(name);
	int i = 0;

	if (index < 0)
		return (NULL);
	while (environ[index][i] != '=')
		i++;
	i++;
	return (&environ[index][i]);
}

/**
 * change_pwd - changes env var to current working directory
 * @name: environmental variable name
 * @prgm: prgm name
 * @count: how many lines user entered
 */
void change_pwd(char *name, char *prgm, int count)
{
	char *pwd, *buf = NULL, *args[4];
	size_t size = 0;
	int env;

	pwd = getcwd(buf, size);
	if (pwd == NULL)
	{
		print_error("Error: mem allocation\n");
		exit(EXIT_FAILURE);
	}
	args[0] = "setenv", args[1] = name, args[2] = pwd, args[3] = NULL;
	env = _setenv(args, prgm, count), env++;
	free(pwd);
}

/**
 * change_oldpwd - changes OLDPWD value to PWD value
 * @prgm: prgm name
 * @count: how many lines user entered
 */
void change_oldpwd(char *prgm, int count)
{
	char *pwd, *args[4];
	int env;

	pwd = _getenv("PWD");
	args[0] = "setenv", args[1] = "OLDPWD", args[2] = pwd, args[3] = NULL;
	env = _setenv(args, prgm, count), env++;
}
