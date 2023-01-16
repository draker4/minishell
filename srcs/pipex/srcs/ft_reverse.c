/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:26:23 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_reverse(t_stack *s)
{
	t_arg	*tmp;

	if (s->top == s->last)
		return ;
	tmp = s->last->prev;
	s->last->next = s->top;
	s->top->prev = s->last;
	s->last->prev = NULL;
	s->top = s->last;
	s->last = tmp;
	s->last->next = NULL;
}

void	ft_reverse_a(t_stack *a, int print)
{
	ft_reverse(a);
	if (print)
		write(1, "rra\n", 4);
}

void	ft_reverse_b(t_stack *b, int print)
{
	ft_reverse(b);
	if (print)
		write(1, "rrb\n", 4);
}

void	ft_reverse_r(t_stack *a, t_stack *b, int print)
{
	ft_reverse(a);
	ft_reverse(b);
	if (print)
		write(1, "rrr\n", 4);
}
