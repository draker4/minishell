/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 13:24:44 by bboisson         ###   ########lyon.fr   */
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
	if (!exec->data->pid[exec->nb])
	{
		change_redir(exec, exec->redir);
		if (exec->outfile == -1 && dup2(exec->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Handle_pipe (exec) - Dup2"), exit(1));
		if (close(exec->fd_pipe[0]) || close(exec->fd_pipe[1]))
			return (perror("Handle_pipe (exec) - Close"), exit(1));
		if (!exec->file_error)
			return (execute_commande(exec));
		return (close_file(exec), exit(1));
	}
	g_exit_status = 0;
	if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
		return (perror("Handle_pipe (next) - Dup2"));
	if (close(exec->fd_pipe[1]) || close(exec->fd_pipe[0]))
		return (perror("Handle_pipe (next) - Close"));
}

static void	last_cmd(t_exec *exec)
{
	int	update_status;
	int	status;

	update_status = 1;
	exec->data->pid[exec->nb] = fork();
	if (exec->data->pid[exec->nb] < 0)
		return (perror("Last_commande - Fork"));
	if (!exec->data->pid[exec->nb])
	{	
		change_redir(exec, exec->redir);
		if (!exec->file_error)
			execute_commande(exec);
		exit(1);
	}
	while (exec->nb >= 0)
	{
		waitpid(exec->data->pid[exec->nb--], &status, WUNTRACED);
		if (update_status)
		{
			if (close(STDIN_FILENO) && close(STDOUT_FILENO)
				&& WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			update_status = 0;
		}
	}
}

void	handle_cmd_list(t_exec *exec)
{
	if (exec->next)
	{
		handle_pipe(exec);
		return (handle_cmd_list(exec->next));
	}
	last_cmd(exec);
}

void	handle_cmd(t_exec *exec)
{
	if (exec->cmd == builtin)
	{
		change_redir(exec, exec->redir);
		if (!exec->file_error)
			return (execute_builtin(exec), close_file(exec));
		return (close_file(exec));
	}
	last_cmd(exec);
}
