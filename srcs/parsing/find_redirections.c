/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:27:05 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 14:50:42 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_input(t_exec *current, int *index)
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
	input->str = current->words[*index];
	last = last_input(current->input);
	if (last)
		last->next = input;
	else
		current->input = input;
	return (1);
}

static int	create_output(t_exec *current, int *index)
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
	last = last_output(current->output);
	if (last)
		last->next = output;
	else
		current->output = output;
	return (1);
}

static int	add_arg(t_exec *current, char *str)
{
	char	**new_arg;
	int		i;

	i = -1;
	if (current->arg)
	{
		new_arg = malloc(sizeof(char *) * (size_arg(current->arg) + 2));
		if (!new_arg)
			return (perror("Add_arg - Malloc:"), 0);
		while (current->arg[++i])
			new_arg[i] = current->arg[i];
		free(current->arg);
		new_arg[i++] = str;
		new_arg[i] = NULL;
	}
	else
	{
		new_arg = malloc(sizeof(char *) * 2);
		if (!new_arg)
			return (perror("Add_arg - Malloc:"), 0);
		new_arg[++i] = str;
		new_arg[++i] = NULL;
	}
	current->arg = new_arg;
	return (1);
}

static int	create_in_out_arg(t_exec *current)
{
	int	i;

	i = 0;
	while (current->words[i])
	{
		if (!ft_strncmp(current->words[i], "<", 1) && current->words[i + 1])
		{
			if (!create_input(current, &i))
				return (0);
		}
		else if (!ft_strncmp(current->words[i], ">", 1) \
		&& current->words[i + 1])
		{
			if (!create_output(current, &i))
				return (0);
		}
		else
		{
			if (!add_arg(current, current->words[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	find_redirections(t_exec **exec)
{
	t_exec	*current;

	current = *exec;
	while (current)
	{
		if (!create_in_out_arg(current))
			return (0);
		current = current->next;
	}
	return (1);
}
