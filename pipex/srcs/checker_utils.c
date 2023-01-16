/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:27:01 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "push_swap.h"

void	ft_get_instruction(t_check **inst, t_check **last)
{
	char	*tmp;

	tmp = get_next_line(0);
	while (tmp)
	{
		if (!ft_check_lst_add_back(tmp, inst, last))
			return (free (tmp), ft_free_check_lst(inst));
		tmp = get_next_line(0);
	}
	free (tmp);
	return ;
}

int	ft_check_instruction(t_check *check)
{
	while (check)
	{
		if (ft_strncmp(check->inst, "sa\n", 4) == 0
			|| ft_strncmp(check->inst, "sb\n", 4) == 0
			|| ft_strncmp(check->inst, "ss\n", 4) == 0
			|| ft_strncmp(check->inst, "pa\n", 4) == 0
			|| ft_strncmp(check->inst, "pb\n", 4) == 0
			|| ft_strncmp(check->inst, "ra\n", 4) == 0
			|| ft_strncmp(check->inst, "rb\n", 4) == 0
			|| ft_strncmp(check->inst, "rr\n", 4) == 0
			|| ft_strncmp(check->inst, "rra\n", 5) == 0
			|| ft_strncmp(check->inst, "rrb\n", 5) == 0
			|| ft_strncmp(check->inst, "rrr\n", 5) == 0)
			check = check->next;
		else
			return (0);
	}
	return (1);
}

int	ft_list_is_sorted(t_stack *a)
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

void	ft_apply_instruction(t_stack *a, t_stack *b, char	*inst)
{
	if (ft_strncmp(inst, "sa\n", 4) == 0)
		ft_swap_a(a, 0);
	else if (ft_strncmp(inst, "sb\n", 4) == 0)
		ft_swap_b(b, 0);
	else if (ft_strncmp(inst, "ss\n", 4) == 0)
		ft_swap_s(a, b, 0);
	else if (ft_strncmp(inst, "pa\n", 4) == 0)
		ft_push_a(a, b, 0);
	else if (ft_strncmp(inst, "pb\n", 4) == 0)
		ft_push_b(a, b, 0);
	else if (ft_strncmp(inst, "ra\n", 4) == 0)
		ft_rotate_a(a, 0);
	else if (ft_strncmp(inst, "rb\n", 4) == 0)
		ft_rotate_b(b, 0);
	else if (ft_strncmp(inst, "rr\n", 4) == 0)
		ft_rotate_r(a, b, 0);
	else if (ft_strncmp(inst, "rra\n", 5) == 0)
		ft_reverse_a(a, 0);
	else if (ft_strncmp(inst, "rrb\n", 5) == 0)
		ft_reverse_b(b, 0);
	else if (ft_strncmp(inst, "rrr\n", 5) == 0)
		ft_reverse_r(a, b, 0);
}
