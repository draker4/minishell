/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 13:56:21 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_free_arg(t_stack *stack)
{
	t_arg	*tmp;
	t_arg	*clear;

	if (stack->top == NULL)
		return (0);
	tmp = stack->top;
	while (tmp)
	{
		clear = tmp;
		tmp = tmp->next;
		free(clear);
	}
	stack->top = NULL;
	return (0);
}

t_arg	*ft_new_arg(int data)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (new == NULL)
		return (NULL);
	new->data = data;
	new->order = -1;
	new->next = NULL;
	return (new);
}

int	ft_add_back(int data, t_stack *a)
{
	t_arg	*new;

	if (a->top == NULL)
	{
		a->top = ft_new_arg(data);
		if (a->top == NULL)
			return (0);
		a->size += 1;
		a->last = a->top;
		return (1);
	}
	new = ft_new_arg(data);
	if (new == NULL)
		return (0);
	a->size += 1;
	new->prev = a->last;
	a->last->next = new;
	a->last = new;
	return (1);
}
