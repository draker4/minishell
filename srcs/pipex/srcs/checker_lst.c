/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 14:17:16 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_free_check_lst(t_check **top)
{
	t_check	*tmp;
	t_check	*clear;

	if (*top == NULL)
		return ;
	tmp = *top;
	while (tmp)
	{
		clear = tmp;
		tmp = tmp->next;
		free(clear->inst);
		free(clear);
	}
	*top = NULL;
}

t_check	*ft_new_check(char *inst)
{
	t_check	*new;

	new = malloc(sizeof(t_check));
	if (new == NULL)
		return (NULL);
	new->inst = inst;
	new->next = NULL;
	return (new);
}

int	ft_check_lst_add_back(char *inst, t_check **top, t_check **last)
{
	t_check	*new;

	if (*top == NULL)
	{
		*top = ft_new_check(inst);
		if (*top == NULL)
			return (0);
		*last = *top;
		return (1);
	}
	new = ft_new_check(inst);
	if (new == NULL)
		return (0);
	new->prev = *last;
	(*last)->next = new;
	*last = new;
	return (1);
}
