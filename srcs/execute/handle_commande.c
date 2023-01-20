/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/20 06:13:57 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commande(t_exec *exec)
{
	int	i;

	i = 0;
	if (ft_strchr(exec->function, '/'))
	{
		execve(exec->function, exec->arg, exec->data->envp);
		return (perror("Execute_commande - Execution (Path)"));
	}
	while (exec->cmd_path[i])
	{
		if (!access(exec->cmd_path[i], F_OK))
			execve(exec->cmd_path[i], exec->arg, exec->data->envp);
		i++;
	}
	perror("Execute_commande - Execution (no path)");
	exit (1);
}

void	handle_pipe(t_exec *exec)
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
		close_file(exec);
		handle_commande(exec->next);
	}
}

void	last_commande(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("Last_commande - Fork"));
	else if (!exec->pid)
	{
		execute_commande(exec);
		exit(1);
	}
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
		return (close_file(exec));
	}
	last_commande(exec);
	close_file(exec);
}

void	execute(t_exec *exec)
{
	if (!exec)
		return ;
	exec->save_stdin = dup(STDIN_FILENO);
	exec->save_stdout = dup(STDOUT_FILENO);
	if (exec->save_stdin == -1 || exec->save_stdout == -1)
		return (perror("Execut - Dup:"));
	handle_commande(exec);
	if (dup2(exec->save_stdin, STDIN_FILENO) == -1 || \
	dup2(exec->save_stdout, STDOUT_FILENO) == -1)
		return (perror("Execut - Dup2:"));
}
