/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bracket_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 19:01:42 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bracket	*new_bracket(char *str, enum e_type type)
{
	t_bracket	*new;

	new = malloc(sizeof(t_bracket));
	if (!new)
		return (perror("New_bracket: "), NULL);
	new->str = str;
	new->prev_exit = -1;
	new->type = type;
	new->next = NULL;
	new->child = NULL;
	new->pipe = NULL;
	new->words = NULL;
	new->standin = 0;
	new->standout = 1;
	new->standerror = 2;
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
		if (clear->child)
			bracket_clear_data(&clear->child);
		tmp = clear;
		clear = clear->next;
		if (tmp->words)
			free_split(tmp->words);
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

t_bracket	*last_bracket(t_bracket *bracket)
{
	t_bracket	*current;

	if (!bracket)
		return (NULL);
	current = bracket;
	while (current->next)
		current = current->next;
	return (current);
}
