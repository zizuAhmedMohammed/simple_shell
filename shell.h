#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdarg.h>

/* global variables */
extern char **environ;
/* Macros */
#define BUFF_SIZE 32

/**
 * struct builtins - struct for built-in commands
 * @str: command
 * @f: function pointer to respective command
 */
typedef struct builtins
{
	char *str;
	int (*f)(char **args, char *prgm, int count);
} builtin_t;

/**
 * struct func_e - struct to store specifier w respective fn
 * @c: format specifier
 * @f: fn ptr that takes param of type va_list
 */
typedef struct func_e
{
	char c;
	int (*f)(va_list);
} func_f;

/* print prompt, getline and tokenize */
void _getprompt(void);
/* ssize_t _getline(char *buff); */
char *_strcpy(char *dest, char *src);
char *my_strtok(char *src, char *delims);
char *_getenv(const char *name);
int get_index(const char *name);
char *_strcat(char *dest, char *src);
int check_slash(char *arg);
int _strcmp(char *s1, char *s2);
size_t _strlen(char *s);
int my_exit(char **args, char *prgm, int count);
char *copy_path(void);
void sig_handler(int signum);
int print_env(char **args, char *prgm, int count);
int my_cd(char **args, char *prgm, int count);
int _unsetenv(char **args, char *prgm, int count);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **create_env(void);
void free_env(void);
int _setenv(char **args, char *prgm, int count);
void check_comment(char **line);
int print_str(va_list ap);
int print_count(va_list ap);
int _putchar(const char c);
int handle_specifiers(va_list args, char c);
int print_error(const char *format, ...);
void change_pwd(char *name, char *prgm, int count);
void change_oldpwd(char *prgm, int count);

#endif /* SHELL_H */
