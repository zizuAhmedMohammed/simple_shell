#include "shell.h"

/**
 * print_str - prints str to stderr
 * @ap: args list
 * Return: -1 if s NULL, num of bytes written otherwise
 */

int print_str(va_list ap)
{
	char *s = va_arg(ap, char *);

	if (s == NULL)
	{
		write(2, "(null)", 6);
		return (-1);
	}
	return (write(2, s, _strlen(s)));
}

/**
 * print_count - prints numbers to stderr
 * @ap: args list
 * Return: num of bytes written
 */

int print_count(va_list ap)
{
	int n = va_arg(ap, int);
	unsigned int place = 1, result = 0, num;

	num = n;
	while (num / place >= 10)
		place *= 10;
	while (place > 0)
	{
		result += _putchar((num / place) % 10 + '0');
		place /= 10;
	}
	return (result);
}

/**
 * _putchar - writes char to stderr
 * @c: char
 * Return: num of bytes written
 */

int _putchar(const char c)
{
	return (write(2, &c, 1));
}

/**
 * handle_specifiers - handles fmt specifiers in print fn
 * @args: args list
 * @c: format specifier
 * Return: num of bytes written
 */

int handle_specifiers(va_list args, char c)
{
	int i = 0;
	func_f arg_list[] = {
		{'s', print_str},
		{'d', print_count},
		{'\0', NULL},
	};
	while (arg_list[i].c)
	{
		if (c == arg_list[i].c)
			return (arg_list[i].f(args));
		i++;
	}
	return (-1);
}

/**
 * print_error - writes to stderr
 * @format: args
 * Return: num of bytes written
 */

int print_error(const char *format, ...)
{
	va_list args;
	unsigned int j, result = 0;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	for (j = 0; format[j]; j++)
	{
		if (format[j] != '%')
			result += _putchar(format[j]);
		else
		{
			j++;
			result += handle_specifiers(args, format[j]);
		}
	}
	va_end(args);
	return (result);
}
