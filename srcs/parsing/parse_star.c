/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:29:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 18:24:55 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !is_in_quote(str, i, 0))
			return (1);
		i++;
	}
	return (0);
}

static int	create_new_redir(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (current->type != delimiter)
			current->str = get_wildcard(current->str);
		current = current->next;
	}
	return (1);
}

static int	delete_star(t_exec *exec, int i)
{
	int		j;
	char	*word_parsed;

	word_parsed = ft_strdup("\0");
	if (!word_parsed)
		return (write(2, "Delete star - ft_strdup\n", 24), 0);
	word_parsed[0] = '\0';
	j = 0;
	while (exec->arg[i][j])
	{
		if (exec->arg[i][j] == '*' && !is_in_quote(exec->arg[i], j, 0))
			j++;
		else
		{
			word_parsed = str_add(word_parsed, exec->arg[i][j]);
			if (!word_parsed)
				return (perror("Delete star - Str add"), 0);
			j++;
		}
	}
	free(exec->arg[i]);
	exec->arg[i] = word_parsed;
	return (1);
}

static int	check_star(t_exec *exec, int i)
{
	char	*copy;

	copy = ft_strdup(exec->arg[i]);
	if (!copy)
		return (perror("Parse_star - ft_strdup"), 0);
	exec->arg[i] = get_wildcard(exec->arg[i]);
	if (!ft_strncmp(copy, exec->arg[i], ft_strlen(copy) + 1) \
	&& (ft_strncmp(exec->arg[0], "export", 8) \
	&& ft_strncmp(exec->arg[0], "unset", 7)))
		if (!delete_star(exec, i))
			return (free(copy), 0);
	free(copy);
	return (1);
}

int	parse_star(t_exec **exec)
{
	t_exec	*tmp;
	int		i;

	tmp = *exec;
	while (tmp)
	{
		i = 0;
		while (tmp->arg && tmp->arg[i])
		{
			if (has_star(tmp->arg[i]))
				if (!check_star(tmp, i))
					return (0);
			i++;
		}
		if (!create_new_redir(tmp->redir))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
