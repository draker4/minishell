/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:04:01 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 12:28:40 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	add_last_redir(t_exec *current, t_redir *redir)
{
	t_redir	*last;

	last = last_redir(current->redir);
	if (last)
		last->next = redir;
	else
		current->redir = redir;
}

int	create_redir(t_exec *current, int *index, int type1, int type2)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (perror("Create_input - Malloc:"), 0);
	redir->next = NULL;
	redir->modif = 0;
	*index += 1;
	if (!ft_strncmp(current->words[*index], "<", 2) || \
	!ft_strncmp(current->words[*index], ">", 2))
	{
		redir->type = type2;
		*index += 1;
	}
	else
		redir->type = type1;
	redir->str = ft_strdup(current->words[*index]);
	if (!redir->str)
		return (free(redir), perror("Create_input - ft_strdup"), 0);
	add_last_redir(current, redir);
	return (1);
}

int	exit_status_redir(t_exec *exec)
{
	t_redir	*tmp;
	char	*str;

	tmp = exec->redir;
	while (tmp)
	{
		if (has_exit_status(tmp->str))
		{
			str = parse_exit_status(tmp->str, g_exit_status);
			if (!str)
				return (0);
			tmp->str = str;
		}
		tmp = tmp->next;
	}
	return (1);
}
