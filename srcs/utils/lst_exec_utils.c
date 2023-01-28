/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:56:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 12:31:12 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*new_exec(char *str, t_data *data, int nb)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (perror("New_exec: "), NULL);
	new->str = str;
	new->data = data;
	new->nb = nb;
	new->file_error = 0;
	new->infile = -1;
	new->outfile = -1;
	new->delimfile = 0;
	new->function = NULL;
	new->redir = NULL;
	new->words = NULL;
	new->delimiter = NULL;
	new->next = NULL;
	new->arg = NULL;
	new->cmd_path = NULL;
	return (new);
}

static void	del_one_exec(t_exec *exec)
{
	if (exec->words)
		free_split(exec->words);
	if (exec->delimiter)
		free(exec->delimiter);
	if (exec->redir)
		redir_clear_data(&exec->redir);
	if (exec->function)
		free(exec->function);
	if (exec->arg)
		free_split(exec->arg);
	if (exec->cmd_path)
		free_split(exec->cmd_path);
	free(exec->str);
	free(exec);
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
		del_one_exec(tmp);
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

int	exec_size(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return (0);
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}
