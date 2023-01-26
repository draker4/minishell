/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:32:11 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 16:07:50 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wild	*new_wild(char *file)
{
	t_wild	*new;

	new = malloc(sizeof(t_wild));
	if (!new)
		return (perror("New_wild - malloc"), NULL);
	new->arg = ft_strdup(file);
	if (!new->arg)
		return (perror("New_wild - ft_strdup"), free(new), NULL);
	new->keep = 0;
	new->next = NULL;
	return (new);
}

void	wild_clear_data(t_wild **wild)
{
	t_wild	*clear;
	t_wild	*tmp;

	if (!wild)
		return ;
	clear = *wild;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
	}
	*wild = NULL;
}

void	wild_add_back(t_wild **wild, t_wild *new)
{
	t_wild	*current;

	if (wild && *wild)
	{
		current = *wild;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (wild)
		*wild = new;
}
