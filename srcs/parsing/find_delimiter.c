/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:52:12 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 17:57:16 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_delimiter(t_exec **exec)
{
	t_exec	*current;
	t_redir	*tmp;

	current = *exec;
	while (current)
	{
		tmp = current->redir;
		while (tmp)
		{
			if (tmp->type == delimiter && has_quote(tmp->str))
				tmp->modif = 1;
			tmp = tmp->next;
		}
		current -= current->next;
	}
	return (1);
}