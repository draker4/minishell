/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_order.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:27:39 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_bloc(t_stack *a, t_stack *b)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a->top)
	{
		j += 100;
		while (i < j && a->top)
		{
			if (a->top->order < j)
			{
				ft_push_b(a, b, 1);
				i++;
			}
			else
				ft_rotate_a(a, 1);
		}
	}
}

void	ft_sort_order(int **order, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if ((*order)[j] > (*order)[i])
			{
				tmp = (*order)[j];
				(*order)[j] = (*order)[i];
				(*order)[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_insert_arg(t_stack *a, int *order)
{
	int		i;
	t_arg	*tmp;

	tmp = a->top;
	while (tmp)
	{
		i = 0;
		while (i < a->size)
		{
			if (tmp->data == order[i])
				tmp->order = i;
			i++;
		}
		tmp = tmp->next;
	}
}

int	ft_define_order(t_stack *a)
{
	int		i;
	int		*order;
	t_arg	*tmp;

	order = malloc(sizeof(int) * a->size);
	if (order == NULL)
		return (ft_putstr_fd("Error\n", 2), 0);
	i = 0;
	tmp = a->top;
	while (tmp)
	{
		order[i++] = tmp->data;
		tmp = tmp->next;
	}
	ft_sort_order(&order, a->size);
	ft_insert_arg(a, order);
	free(order);
	return (1);
}
