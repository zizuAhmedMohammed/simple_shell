#include "shell.h"

/**
 * _strchr - locate char in string
 * @delim: string
 * @c: byte to search for
 * Return: ptr delim, or NULL
 */
char *_strchr(char *delim, int c)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (delim);
		delim++;
	}
	return (NULL);

}

/**
 * _strcspn - search a string for a set of bytes
 * @str1: string to search
 * @str2: string to reject in search
 * Return: number of bytes in init segment not in reject
 */
size_t _strcspn(const char *str1, const char *str2)
{
	size_t i, j;

	for (i = 0; str1[i] != '\0'; ++i)
	{
		for (j = 0; str2[j] != '\0'; ++j)
		{
			if (str1[i] == str2[j])
				return (i);
		}
	}
	return (i);
}

/**
 * my_strtok - extract tokens from strings
 * @s: string to parse
 * @delim: delimiter
 * Return: ptr to next token, NULL if no more tokens
 */
char *my_strtok(char *s, char *delim)
{
	static char *lasts;
	int ch;

	if (s == 0)
		s = lasts;
	do {
		ch = *s++;
		if (ch  == '\0')
		{
			return (0);
		}
	} while (_strchr(delim, ch));
	--s;
	lasts = s + _strcspn(s, delim);
	if (*lasts != 0)
		*lasts++ = 0;
	return (s);
}
