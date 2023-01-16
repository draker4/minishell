/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:29:26 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack *a)
{
	if (a->size == 1)
		return ;
	else if (a->size == 2)
	{
		if (a->top->data > a->top->next->data)
			ft_swap_a(a, 1);
		return ;
	}
	if (a->top->next->data < a->top->data && a->top->data < a->last->data)
		return (ft_swap_a(a, 1));
	else if (a->last->data < a->top->next->data
		&& a->top->next->data < a->top->data)
		return (ft_swap_a(a, 1), ft_reverse_a(a, 1));
	else if (a->top->next->data < a->last->data && a->last->data < a->top->data)
		return (ft_rotate_a(a, 1));
	else if (a->top->data < a->last->data && a->last->data < a->top->next->data)
		return (ft_swap_a(a, 1), ft_rotate_a(a, 1));
	else if (a->last->data < a->top->data && a->top->data < a->top->next->data)
		return (ft_reverse_a(a, 1));
}

int	ft_define_min(t_stack *a)
{
	int		i;
	int		j;
	int		min;
	t_arg	*tmp;

	min = a->top->data;
	tmp = a->top->next;
	i = 0;
	j = 0;
	while (tmp)
	{
		j++;
		if (tmp->data < min)
		{
			i = j;
			min = tmp->data;
		}
		tmp = tmp->next;
	}
	if (i > a->size / 2)
		i = i - a->size;
	return (i);
}

void	ft_push_min(t_stack *a, t_stack *b)
{
	int	i;

	i = ft_define_min(a);
	if (i > 0)
	{
		while (i-- > 0)
			ft_rotate_a(a, 1);
	}
	else if (i < 0)
	{
		while (i++ < 0)
			ft_reverse_a(a, 1);
	}
	ft_push_b(a, b, 1);
}

void	ft_sort_five(t_stack *a, t_stack *b)
{
	ft_push_min(a, b);
	if (a->size == 5 - 1)
		ft_push_min(a, b);
	ft_sort_three(a);
	ft_push_a(a, b, 1);
	if (a->size == 5 - 1)
		ft_push_a(a, b, 1);
}
