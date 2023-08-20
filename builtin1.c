#include "shell.h"

/**
 * _myhistory - display the historys lists, ones commands by lines, preced
 *              with lines number, starting at 0.
 * @info: Structures containings potentials argument. Used to maintain
 *        constants functions prototypes
 *  Return:  0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - set alia to string
 * @info: parameters structs
 * @str: the strings alia
 *
 * Return: Alway 0 on successes, 1 at errors
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;
	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * set_alias - set alia to strings
 * @info: parameters structs
 * @str: the strings alia
 *
 * Return: Alway 0 at an success, 1 if error
 */
int set_alias(info_t *info, char *str)
{
	char *p;
	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - print an alia strings
 * @node: the aliass nodes
 *
 * Return: Alway 0 at successes, 1 on an error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;
	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structures containinng potentiall argument. Useds in maintain
 *          constants functions prototyps
 *  Return: Alway 0,
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
