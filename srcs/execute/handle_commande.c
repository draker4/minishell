/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/27 20:07:15 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	handle_pipe(t_exec *exec)
{
	pipe(exec->fd_pipe);
	exec->data->pid[exec->nb] = fork();
	if (exec->data->pid[exec->nb] < 0)
		return (perror("Handle_pipe - Fork: "));
	else if (!exec->data->pid[exec->nb])
	{
		if (exec->redir && change_redir(exec))
		{
			exec->file_error = 1;
			if (!exec->next)
				return ;
		}
		if (!exec->redir && dup2(exec->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Handle_pipe (exec) - Dup2"), exit(1));
		if (close(exec->fd_pipe[0]) || close(exec->fd_pipe[1]))
			return (perror("Handle_pipe (exec) - Close"), exit(1));
		if (exec->file_error)
			exit(0);
		execute_commande(exec);
	}
	else
	{
		g_exit_status = 0;
		if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
			return (perror("Handle_pipe (next) - Dup2"));
		if (close(exec->fd_pipe[1]) || close(exec->fd_pipe[0]))
			return (perror("Handle_pipe (next) - Close"));
	}
}

static void	last_cmd(t_exec *exec)
{
	int	update_status;
	int	status;

	update_status = 1;
	exec->data->pid[exec->nb] = fork();
	if (exec->data->pid[exec->nb] < 0)
		return (perror("Last_commande - Fork"));
	else if (!exec->data->pid[exec->nb])
	{	
		if (exec->redir && change_redir(exec))
		{
			exec->file_error = 1;
			if (!exec->next)
				return ;
		}
		execute_commande(exec);
	}
	else
	{
		while (exec->nb >= 0)
		{
			waitpid(exec->data->pid[exec->nb--], &status, WUNTRACED);
			if (update_status)
			{
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				if (WIFEXITED(status))
					g_exit_status = WEXITSTATUS(status);
				update_status = 0;
			}
		}
	}
}

void	handle_cmd_list(t_exec *exec)
{
	if (!change_exit_status(exec))
		return ;
	if (exec->next)
	{
		handle_pipe(exec);
		close_file(exec);
		return (handle_cmd_list(exec->next));
	}
	last_cmd(exec);
	close_file(exec);
}

void	handle_cmd(t_exec *exec)
{
	if (!change_exit_status(exec))
		return ;
	if (exec->redir && change_redir(exec))
		return ;
	if (exec->cmd == builtin)
		return (execute_builtin(exec), close_file(exec));
	last_cmd(exec);
	close_file(exec);
}
