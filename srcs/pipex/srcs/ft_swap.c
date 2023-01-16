/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:26:33 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stack *s)
{
	t_arg	*first;
	t_arg	*second;
	int		last_change;

	if (s->top == NULL || s->top->next == NULL)
		return ;
	last_change = 0;
	if (s->top->next == s->last)
		last_change = 1;
	first = s->top->next;
	first->prev = NULL;
	second = s->top;
	second->next = s->top->next->next;
	first->next = second;
	second->prev = first;
	if (second->next)
		second->next->prev = second;
	s->top = first;
	if (last_change == 1)
		s->last = second;
}

void	ft_swap_a(t_stack *a, int print)
{
	ft_swap(a);
	if (print)
		write(1, "sa\n", 3);
}

void	ft_swap_b(t_stack *b, int print)
{
	ft_swap(b);
	if (print)
		write(1, "sb\n", 3);
}

void	ft_swap_s(t_stack *a, t_stack *b, int print)
{
	ft_swap(a);
	ft_swap(b);
	if (print)
		write(1, "ss\n", 3);
}
