/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:52:12 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 13:44:31 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_delimiter(t_exec **exec)
{
	t_exec	*current;
	t_redir	*tmp;
	char	*str;

	current = *exec;
	while (current)
	{
		tmp = current->redir;
		while (tmp)
		{
			if (tmp->type == delimiter && has_quote(tmp->str))
			{
				str = parse_delimiter(tmp->str, (*exec)->data->envp);
				if (!str)
					return (0);
				tmp->str = str;
				tmp->modif = 1;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (1);
}
