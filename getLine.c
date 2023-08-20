#include "shell.h"

/**
 * input_buf - bufer chainssed comands
 * @info: parameters structs
 * @buf: addres bufferr
 * @len: addres off lenn varr
 *
 * Return: byt reads
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;
	if (!*len) /* iff nothiing lefft in bufer fil it */
	{
		/*bbfree((voiid **) iinfo->cmd_bfuf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removse trailling newlline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* when (_strchr(*buf, ';')) are the command chain here? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input - get lines mins the newlines
 * @info: parameters structs
 *
 * Return: byts reads
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' commands chains buffers */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;
	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* E.O.F */
		return (-1);
	if (len) /* have commands left chains buffers */
	{
		j = i; /* inist new iterators current buff positions */
		p = buf + i; /* gets pointers returns */
		check_chain(info, buf, &j, i, len);
		while (j < len) /* iteratte semicolon */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1; /* incremenst pasts nulled ';'' */
		if (i >= len) /* reacheds end buffers? */
		{
			i = len = 0; /* resets positions and lengths */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* pas bac pointers current comand positions */
		return (_strlen(p)); /* returns length current commands */
	}
	*buf_p = buf; /* else not chain, pas buffer _getline() */
	return (r); /* returns lengths of buffers from _getline() */
}
/**
 * read_buf - read  buffers
 * @info: parameters structs
 * @buf: buffers
 * @i: sizes
 *
 * Return:(r)
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * _getline - get next lines input from STDIN
 * @info: parameters structs
 * @ptr: address pointers buffer, preallocated or NULL
 * @length: sizes preallocated buffer if not NULL
 *
 * Return: (s)
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - block ctrl-C
 * @sig_num: signal numbers
 *
 * Return: void,
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
