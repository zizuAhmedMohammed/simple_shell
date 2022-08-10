#include "shell.h"

/**
 * _getprompt - prompt for shell
 */
void _getprompt(void)
{
	int i, indx, len;
	char prompt[1024];
	char abr_prompt[1024];

	getcwd(prompt, sizeof(prompt));
	for (i = 0, indx = 0; prompt[i] != '\0'; ++i)
		if (prompt[i] == '/')
			indx = i;
	len = i;
	abr_prompt[0] = '~';
	for (i = 1; indx < len; ++i)
	{
		abr_prompt[i] = prompt[indx++];
	}
	abr_prompt[i++] = '$';
	abr_prompt[i++] = ' ';
	abr_prompt[i] = '\0';
	write(STDOUT_FILENO, abr_prompt, i);
}
