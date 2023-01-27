/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:29:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 18:09:55 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !is_in_quote(str, i))
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
		current->str = get_wildcard(current->str);
		current = current->next;
	}
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
				tmp->arg[i] = get_wildcard(tmp->arg[i]);
			i++;
		}
		if (!create_new_redir(tmp->redir))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
