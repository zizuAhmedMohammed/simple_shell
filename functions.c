#include "shell.h"

/**
 * parse_args - uses strtok to parse args and store in a buffer
 * @line: user input from getline()
 * @delim: set delimiter for tokenizer
 * Return: ptr to strings of args
 */

char **parse_args(char *line, char *delim)
{
	size_t i = 0, len = BUFF_SIZE, new_size;
	char *token;
	char **args = malloc(len * sizeof(char *));

	if (args == NULL)
		return (NULL);
	token = my_strtok(line, delim);
	while (token != NULL)
	{
		args[i] = token;
		i++;
		if (i >= len)
		{
			new_size = len * 2;
			args = _realloc(args, len * sizeof(char *), new_size * sizeof(char *));
			if (args == NULL)
			{
				print_error("Error: mem allocation\n");
				exit(EXIT_FAILURE);
			}
			len = new_size;
		}
		token = my_strtok(NULL, delim);
	}
	args[i] = NULL;
	return (args);
}

/**
 * check_slash - checks if argument has a forward slash character
 * @arg: ptr to an arg
 * Return: 1 if args has slash, 0 otherwise
 */

int check_slash(char *arg)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/**
 * check_builtin - check if command is a built-in
 * @args: ptr to str of args
 * @prgm: name of the program (used to print error)
 * @count: count of user input (used to print error)
 * Return: index of the cmd, or -1 if not found
 */

int check_builtin(char **args, char *prgm, int count)
{
	int i = 0;
	builtin_t built_func[] = {
		{"exit", my_exit},
		{"cd", my_cd},
		{"env", print_env},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{NULL, NULL}
	};

	while (built_func[i].str != NULL)
	{
		if (_strcmp(args[0], built_func[i].str) == 0)
			return (built_func[i].f(args, prgm, count));
		i++;
	}
	return (117);
}

/**
 * exec_cmd - executes commands, searches PATH if no command location given
 * @args: parsed args buffer
 * @path: parsed buffer of path
 * @prgm: name of program
 * @count: number of user input
 */

void exec_cmd(char **args, char **path, char *prgm, int count)
{
	int i = 0;
	size_t path_space = 31, len = _strlen(args[0]) + path_space + 1;
	char *buffer_path;

	if (check_slash(ags[0]))
	{
		if (execve(args[0], args, NULL) == -1)
		{
			print_error("%s: %d: %s: not found\n", prgm, count, args[0]);
			_exit(127);
		}
	}
	else
	{
		buffer_path = malloc(len * sizeof(char));
		if (buffer_path == NULL)
			exit(EXIT_FAILURE);
		/* this loop checks user's cmd against PATH dirs, executes cmd if found */
		for ( ; path[i]; i++)
		{
			if ((_strlen(path[i])) >= path_space)
			{
				buffer_path = _realloc(buffer_path, len, _strlen(path[i]));
				if (buffer_path == NULL)
					exit(EXIT_FAILURE);
			}
			_strcpy(buffer_path, path[i]);
			_strcat(buffer_path, "/");
			_strcat(buffer_path, args[0]);
			if (execve(buffer_path, args,(NULL) != -1)
				break;
		}
		/*************************************************************************/
		free(buffer_path);
		if (path[i] == NULL)
		{
			print_error("%s: %d: %s: not found\n", prgm, count, args[0]);
			_exit(1);
		}
	}
}

/**
 * main - shell: prompts user for input, tries to interpret input as commands
 * @argc: arg count
 * @argv: arg vector
 * Return: 0
 */

int main(int __attribute__((unused)) argc, char *argv[])
{
	int is_builtin, status, count = 0;
	pid_t child_pid;
	ssize_t bytes;
	size_t n = 0;
	char *line = NULL, **args, **path, **my_env = create_env(), *path_val = NULL;

	environ = my_env;
	while (1)
	{
		count++;
		signal(SIGINT, sig_handler);	/* handler: ^C prompts instead of terminate  */
		_getprompt();	/* prints shell prompt */
		bytes = getline(&line, &n, stdin);	/* read user's keyboard input */
		if (bytes == EOF)
			break;
		if (line[0] == '#')
			continue;
		check_comment(&line);	/* looks for '#' so comments ignored in input */
		args = parse_args(line, "\n \t\r");
		/* copy and parse PATH - copied so environ PATH unaffected after parsing */
		path_val = copy_path();
		path = parse_args(path_val, ":\n");
		/*************************************************************************/
		is_builtin = check_builtin(args, argv[0], count);
		/* if cmd not built-in, create child process and check PATH for valid cmd */
		if (is_builtin == 117)
		{
			child_pid = fork();
			if (child_pid == -1)
				perror("fork");
			if (child_pid == 0)
				exec_cmd(args, path, argv[0], count);
			else
				wait(&status);
		}
		free(args), free(path_val), free(path);
	}
	free(line), free_env();
	return (0);
}
