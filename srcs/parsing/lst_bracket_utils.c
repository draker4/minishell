/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bracket_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 09:28:12 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bracket	*new_bracket(char *str, enum e_type type)
{
	t_bracket	*new;

	new = malloc(sizeof(t_bracket));
	if (!new)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	new->str = str;
	new->prev_exit = -1;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	bracket_clear_data(t_bracket **bracket)
{
	t_bracket	*clear;
	t_bracket	*tmp;

	if (!bracket)
		return ;
	clear = *bracket;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		free(tmp->str);
		free(tmp);
	}
	*bracket = NULL;
}

void	bracket_add_back(t_bracket **bracket, t_bracket *new)
{
	t_bracket	*current;

	if (bracket && *bracket)
	{
		current = *bracket;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (bracket)
		*bracket = new;
}
