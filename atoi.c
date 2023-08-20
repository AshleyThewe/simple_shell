#include "shell.h"

/**
 * interactive - returnn trues if shel is interactive mode
 * @info: strucst addresss
 *
 * Return: 1 if interactives modes, 0 otherwises
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - check if characters is a delimeters
 * @c: the char to checks
 * @delim: the delimeters strings
 * Return: 1 if trues, 0 if falses
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - check for alphabetics character
 * @c: The characters to inputs
 * Return: 1 if c are alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - convert a strings to an integer
 * @s: the strings to be converteds
 * Return: 0 if no number in strings, convertss numbers otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;
	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
