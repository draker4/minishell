/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:26:15 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push(t_stack *s1, t_stack *s2)
{
	t_arg	*tmp1;
	t_arg	*tmp2;
	int		last_change_top1;
	int		last_change_top2;

	if (s1->top == NULL)
		return ;
	last_change_top1 = 0;
	if (s1->top == s1->last)
		s1->last = NULL;
	last_change_top2 = 0;
	if (s2->last == NULL)
		s2->last = s1->top;
	tmp1 = s1->top->next;
	tmp2 = s2->top;
	s2->top = s1->top;
	s2->top->next = tmp2;
	if (s2->top->next)
		s2->top->next->prev = s1->top;
	s1->top = tmp1;
	if (s1->top)
		s1->top->prev = NULL;
	s1->size -= 1;
	s2->size += 1;
}

void	ft_push_a(t_stack *a, t_stack *b, int print)
{
	if (a->top == NULL)
	{
		a->min = b->top->order;
		a->max = b->top->order;
	}
	else if (b->top && b->top->order < a->min)
		a->min = b->top->order;
	else if (b->top && b->top->order > a->max)
		a->max = b->top->order;
	ft_push(b, a);
	if (print)
		write(1, "pa\n", 3);
}

void	ft_push_b(t_stack *a, t_stack *b, int print)
{
	ft_push(a, b);
	if (print)
		write(1, "pb\n", 3);
}
