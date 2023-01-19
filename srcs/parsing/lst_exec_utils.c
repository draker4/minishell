/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/19 17:00:37 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*new_exec(char *str, t_data *data)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (perror("New_bracket: "), NULL);
	new->str = str;
	new->data = data;
	new->function = NULL;
	new->input = NULL;
	new->output = NULL;
	new->words = NULL;
	new->delimiter = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->arg = NULL;
	return (new);
}

void	exec_clear_data(t_exec **exec)
{
	t_exec	*clear;
	t_exec	*tmp;

	if (!exec)
		return ;
	clear = *exec;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		if (tmp->words)
			free_split(tmp->words);
		if (tmp->delimiter)
			free(tmp->delimiter);
		if (tmp->input)
			input_clear_data(&tmp->input);
		if (tmp->output)
			output_clear_data(&tmp->output);
		if (tmp->function)
			free(tmp->function);
		free(tmp->str);
		free(tmp);
	}
	*exec = NULL;
}

void	exec_add_back(t_exec **exec, t_exec *new)
{
	t_exec	*current;

	if (exec && *exec)
	{
		current = *exec;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (exec)
		*exec = new;
}
