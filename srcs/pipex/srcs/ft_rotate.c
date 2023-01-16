/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:26:28 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate(t_stack *s)
{
	t_arg	*tmp;

	if (s->top == s->last)
		return ;
	tmp = s->top->next;
	s->top->prev = s->last;
	s->last->next = s->top;
	s->top->next = NULL;
	s->last = s->top;
	s->top = tmp;
	s->top->prev = NULL;
}

void	ft_rotate_a(t_stack *a, int print)
{
	ft_rotate(a);
	if (print)
		write(1, "ra\n", 3);
}

void	ft_rotate_b(t_stack *b, int print)
{
	ft_rotate(b);
	if (print)
		write(1, "rb\n", 3);
}

void	ft_rotate_r(t_stack *a, t_stack *b, int print)
{
	ft_rotate(a);
	ft_rotate(b);
	if (print)
		write(1, "rr\n", 3);
}
