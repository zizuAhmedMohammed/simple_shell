#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}
