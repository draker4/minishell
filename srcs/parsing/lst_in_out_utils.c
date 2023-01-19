/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_in_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:36:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/19 16:44:40 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*last_input(t_input *input)
{
	t_input	*current;

	if (!input)
		return (NULL);
	current = input;
	while (current->next)
		current = current->next;
	return (current);
}

t_output	*last_output(t_output *output)
{
	t_output	*current;

	if (!output)
		return (NULL);
	current = output;
	while (current->next)
		current = current->next;
	return (current);
}

void	input_clear_data(t_input **input)
{
	t_input	*clear;
	t_input	*tmp;

	if (!input)
		return ;
	clear = *input;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		free(tmp);
	}
	*input = NULL;
}

void	output_clear_data(t_output **output)
{
	t_output	*clear;
	t_output	*tmp;

	if (!output)
		return ;
	clear = *output;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		free(tmp);
	}
	*output = NULL;
}
