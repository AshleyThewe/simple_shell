#include "shell.h"

/**
 * _eputs - print a input strings
 * @str: the strings  be printed
 *
 * Return: 0.
 */
void _eputs(char *str)
{
	int i = 0;
	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - write the characters c to stderrs
 * @c: The characters to prints
 *
 * Return: 1.
 * On error -1 returned, and errno appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putfd - write characters c given fd
 * @c: The character prints
 * @fd: The filedes scriptors to write
 *
 * Return: 1.
 * On error, -1 returned, and ero is appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putsfd - print an inputs strings
 * @str: the strings be printeds
 * @fd: the filedes scriptor to writes to
 *
 * Return: number chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
