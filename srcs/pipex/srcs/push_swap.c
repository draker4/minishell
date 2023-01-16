/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 13:37:19 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_already_sort(t_stack *a)
{
	t_arg	*tmp;

	tmp = a->top;
	while (tmp->next)
	{
		if (tmp->data > tmp->next->data)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_push_swap(t_stack *a, t_stack *b)
{
	if (ft_already_sort(a))
		return ;
	else if (a->size <= 3)
		return (ft_sort_three(a));
	else if (a->size <= 5)
		return (ft_sort_five(a, b));
	if (!ft_define_order(a))
		return ;
	ft_push_bloc(a, b);
	while (b->top)
	{
		ft_define_next_move(a, b);
		ft_realise_move(a, b);
	}
	ft_final_sort(a);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	a.size = 0;
	a.top = NULL;
	a.last = NULL;
	ft_parse(argc, argv, &a);
	if (a.top == NULL)
		return (0);
	b.size = 0;
	b.top = NULL;
	b.last = NULL;
	ft_push_swap(&a, &b);
	if (a.top)
		ft_free_arg(&a);
	if (b.top)
		ft_free_arg(&b);
	return (0);
}
