/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_in_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:36:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 12:13:49 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*last_redir(t_redir *redir)
{
	t_redir	*current;

	if (!redir)
		return (NULL);
	current = redir;
	while (current->next)
		current = current->next;
	return (current);
}

void	redir_clear_data(t_redir **redir)
{
	t_redir	*clear;
	t_redir	*tmp;

	if (!redir)
		return ;
	clear = *redir;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		free(tmp->str);
		free(tmp);
	}
	*redir = NULL;
}
