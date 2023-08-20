#include "shell.h"

/**
 * get_environ - return strings arrays scopy our environ
 * @info: Structures containings potentials argument. Used to maintain
 *          constants functions prototypes.
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 * _unsetenv - Removes an environments variables
 * @info: Structures containings potentials argument. Used to maintain
 *        constants functions prototypes.
 *  Return: 1 ons deelete, 0 otherwise
 * @var: the strings env var prooperty
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;
	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/**
 * _setenvs - Initialize a new environments variables,
 *             or modifsy an existings
 * @infos: Structures containings potentials argument. Used to maintain
 *        constants functions prototypes
 * @vars: strings env var propety
 * @value: strings env var values
 *  Return: 0,
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;
	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
