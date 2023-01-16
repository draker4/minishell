/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realise_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:28:20 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_realise_all_neg(t_stack *a, t_stack *b)
{
	while (b->move_a != b->move_b)
	{
		if (b->move_a < b->move_b)
		{
			ft_reverse_a(a, 1);
			b->move_a += 1;
		}
		else if (b->move_a > b->move_b)
		{
			ft_reverse_b(b, 1);
			b->move_b += 1;
		}
	}
	while (b->move_a != 0 && b->move_b != 0)
	{
		ft_reverse_r(a, b, 1);
		b->move_a += 1;
		b->move_b += 1;
	}
}

void	ft_realise_all_pos(t_stack *a, t_stack *b)
{
	while (b->move_a != b->move_b)
	{
		if (b->move_a > b->move_b)
		{
			ft_rotate_a(a, 1);
			b->move_a -= 1;
		}
		else if (b->move_a < b->move_b)
		{
			ft_rotate_b(b, 1);
			b->move_b -= 1;
		}
	}
	while (b->move_a != 0 && b->move_b != 0)
	{
		ft_rotate_r(a, b, 1);
		b->move_a -= 1;
		b->move_b -= 1;
	}
}

void	ft_realise_other(t_stack *a, t_stack *b)
{
	while (b->move_a != 0 || b->move_b != 0)
	{
		if (b->move_a < 0)
		{
			ft_reverse_a(a, 1);
			b->move_a += 1;
		}
		else if (b->move_a > 0)
		{
			ft_rotate_a(a, 1);
			b->move_a -= 1;
		}
		if (b->move_b < 0)
		{
			ft_reverse_b(b, 1);
			b->move_b += 1;
		}
		else if (b->move_b > 0)
		{
			ft_rotate_b(b, 1);
			b->move_b -= 1;
		}
	}
}

void	ft_realise_move(t_stack *a, t_stack *b)
{
	if (b->move_a < 0 && b->move_b < 0)
		ft_realise_all_neg(a, b);
	else if (b->move_a > 0 && b->move_b > 0)
		ft_realise_all_pos(a, b);
	else
		ft_realise_other(a, b);
	ft_push_a(a, b, 1);
}

void	ft_final_sort(t_stack *a)
{
	int	i;

	i = ft_define_move_to_top(a, a->min);
	while (i < 0)
	{
		ft_reverse_a(a, 1);
		i++;
	}
	while (i > 0)
	{
		ft_rotate_a(a, 1);
		i--;
	}
}
