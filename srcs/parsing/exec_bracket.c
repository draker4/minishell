/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:42:11 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 15:40:52 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	parse_words(t_bracket **bracket)
// {
// 	(void)bracket;
// 	return (1);
// }

// static int	create_child(t_bracket **bracket)
// {
	
// }

// void	exec_brackets(t_minishell *minishell)
// {
// 	t_bracket	*current;

// 	current = minishell->bracket;
// 	while (current)
// 	{
// 		if (!has_brackets(current->str))
// 		{
// 			if (!parse_words(&current))
// 				return ;
// 		}
// 		else
// 		{
// 			if (!create_childs(&current))
// 				return ;
// 		}
// 		current = current->next;
// 	}
// 	while (minishell->bracket)
// 	{
// 		printf("ici bracket = %s et enum=%d\n", minishell->bracket->str, minishell->bracket->type);
// 		minishell->bracket = minishell->bracket->next;
// 	}
// }
