/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:43:27 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_checker(t_stack *a, t_stack *b)
{
	t_check	*inst;
	t_check	*last;
	t_check	*apply;

	inst = NULL;
	last = NULL;
	ft_get_instruction(&inst, &last);
	if (!ft_check_instruction(inst))
		return (ft_putstr_fd("Error\n", 2), ft_free_check_lst(&inst));
	apply = inst;
	while (apply)
	{
		ft_apply_instruction(a, b, apply->inst);
		apply = apply->next;
	}
	if (b->top)
		return (ft_printf("KO\n"), ft_free_check_lst(&inst));
	else if (!ft_list_is_sorted(a))
		return (ft_printf("KO\n"), ft_free_check_lst(&inst));
	return (ft_printf("OK\n"), ft_free_check_lst(&inst));
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
	ft_checker(&a, &b);
	if (a.top)
		ft_free_arg(&a);
	if (b.top)
		ft_free_arg(&b);
	return (0);
}
