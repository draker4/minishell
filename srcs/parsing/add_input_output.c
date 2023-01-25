/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:04:01 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 12:50:01 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_input(t_exec *current, int *index)
{
	t_input	*input;
	t_input	*last;

	input = malloc(sizeof(t_input));
	if (!input)
		return (perror("Create_input - Malloc:"), 0);
	input->next = NULL;
	input->file = -1;
	*index += 1;
	if (!ft_strncmp(current->words[*index], "<", 1))
	{
		input->in = delimiter;
		*index += 1;
	}
	else
		input->in = in_file;
	input->str = ft_strdup(current->words[*index]);
	if (!input->str)
		return (perror("Create_input - ft_strdup"), 0);
	last = last_input(current->input);
	if (last)
		last->next = input;
	else
		current->input = input;
	return (1);
}

int	create_output(t_exec *current, int *index)
{
	t_output	*output;
	t_output	*last;

	output = malloc(sizeof(t_output));
	if (!output)
		return (perror("Create_output - Malloc:"), 0);
	output->next = NULL;
	output->file = -1;
	*index += 1;
	if (!ft_strncmp(current->words[*index], ">", 1))
	{
		output->out = append;
		*index += 1;
	}
	else
		output->out = out_file;
	output->str = current->words[*index];
	if (!output->str)
		return (perror("Create_output - ft_strdup"), 0);
	last = last_output(current->output);
	if (last)
		last->next = output;
	else
		current->output = output;
	return (1);
}

int	exit_status_input(t_exec *exec)
{
	t_input	*tmp;
	char	*str;

	tmp = exec->input;
	while (tmp)
	{
		if (has_exit_status(tmp->str))
		{
			str = parse_exit_status(tmp->str);
			if (!str)
				return (0);
			tmp->str = str;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	exit_status_output(t_exec *exec)
{
	t_output	*tmp;
	char		*str;

	tmp = exec->output;
	while (tmp)
	{
		if (has_exit_status(tmp->str))
		{
			str = parse_exit_status(tmp->str);
			if (!str)
				return (0);
			tmp->str = str;
		}
		tmp = tmp->next;
	}
	return (1);
}
