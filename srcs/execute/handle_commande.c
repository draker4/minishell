/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/23 12:42:02 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_exec *exec)
{
	pipe(exec->fd_pipe);
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("Handle_pipe - Fork: "));
	else if (!exec->pid)
	{
		if (close(exec->fd_pipe[0]))
			return (perror("Handle_pipe (exec) - Close"), exit (1));
		if (dup2(exec->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Handle_pipe (exec) - Dup2"), exit (1));
		execute_commande(exec);
	}
	else
	{
		if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
			return (perror("Handle_pipe (next) - Dup2"));
		if (close(exec->fd_pipe[1]))
			return (perror("Handle_pipe (next) - Close"));
		waitpid(exec->pid, &exec->data->exit_status, 0);
	}
}

static void	last_commande(t_exec *exec)
{
	if (exec->cmd == builtin)
		return (execute_builtin(exec));
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("Last_commande - Fork"));
	else if (!exec->pid)
		execute_commande(exec);
	else
		waitpid(exec->pid, &exec->data->exit_status, 0);
}

void	handle_commande(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->input)
	{
		if (change_input(exec->input))
		{
			close_file(exec);
			if (exec->next)
				handle_commande(exec->next);
			return ;
		}
	}
	if (exec->output)
		if (change_output(exec->output))
			return (close_file(exec));
	if (exec->next)
	{
		handle_pipe(exec);
		close_file(exec);
		return (handle_commande(exec->next));
	}
	last_commande(exec);
	close_file(exec);
}
