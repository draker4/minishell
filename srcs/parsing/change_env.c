/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:28:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 11:41:05 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_env_redir(t_redir *current, char **envp)
{
	t_redir	*tmp;
	char	*parse_word;

	tmp = current;
	while (tmp)
	{
		if (tmp->type != delimiter)
		{
			parse_word = parse_env_only(tmp->str, envp);
			if (!parse_word)
				return (0);
			free(tmp->str);
			tmp->str = parse_word;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	change_env(t_exec **exec)
{
	t_exec	*current;
	char	*parse_word;
	int		i;

	current = *exec;
	while (current)
	{
		i = 0;
		while (current->arg && current->arg[i])
		{
			parse_word = parse_env_only(current->arg[i], current->data->envp);
			if (!parse_word)
				return (0);
			free(current->arg[i]);
			current->arg[i] = parse_word;
			i++;
		}
		if (!change_env_redir(current->redir, current->data->envp))
			return (0);
		current = current->next;
	}
	return (1);
}
