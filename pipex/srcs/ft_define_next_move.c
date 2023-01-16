/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_next_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 15:54:41 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_define_move_to_top(t_stack *stack, int order)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = stack->top;
	while (tmp)
	{
		if (tmp->order == order)
		{
			if (i > stack->size / 2)
				i = i - stack->size;
			return (i);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	ft_define_move_prepare_a(t_stack *a, int order)
{
	t_arg	*tmp;

	if (a->top == NULL || a->top == a->last)
		return (0);
	else if (order < a->min || a->max < order)
		return (ft_define_move_to_top(a, a->min));
	else if (a->last->order < order && order < a->top->order)
		return (0);
	else
	{
		tmp = a->top;
		while (tmp->next)
		{
			if (tmp->order < order && order < tmp->next->order)
				return (ft_define_move_to_top(a, tmp->next->order));
			tmp = tmp->next;
		}
	}
	return (-1);
}

void	ft_update_best_move(t_stack *b, t_arg *tmp, int total)
{
	if (total < b->move_total)
	{
		b->move_total = total;
		b->move_a = tmp->move_a;
		b->move_b = tmp->move_b;
	}
}

void	ft_check_best_move(t_stack *b, t_arg *tmp)
{
	if (tmp->move_a < 0 && tmp->move_b < 0)
	{
		if (tmp->move_a < tmp->move_b)
			return (ft_update_best_move(b, tmp, tmp->move_a * -1));
		else if (tmp->move_a > tmp->move_b)
			return (ft_update_best_move(b, tmp, tmp->move_b * -1));
	}
	else if (tmp->move_a >= 0 && tmp->move_b >= 0)
	{
		if (tmp->move_a >= tmp->move_b)
			return (ft_update_best_move(b, tmp, tmp->move_a));
		else if (tmp->move_a < tmp->move_b)
			return (ft_update_best_move(b, tmp, tmp->move_b));
	}
	else
	{
		if (tmp->move_a < 0)
			return (ft_update_best_move(b, tmp,
					tmp->move_a * -1 + tmp->move_b));
		else if (tmp->move_b < 0)
			return (ft_update_best_move(b, tmp,
					tmp->move_a + tmp->move_b * -1));
	}
}

void	ft_define_next_move(t_stack *a, t_stack *b)
{
	t_arg	*tmp;

	tmp = b->top;
	if (b->size > a->size)
		b->move_total = b->size;
	else if (b->size <= a->size)
		b->move_total = a->size;
	while (tmp)
	{
		tmp->move_b = ft_define_move_to_top(b, tmp->order);
		if (tmp->move_b < b->move_total)
		{
			tmp->move_a = ft_define_move_prepare_a(a, tmp->order);
			ft_check_best_move(b, tmp);
		}
		tmp = tmp->next;
	}
}
