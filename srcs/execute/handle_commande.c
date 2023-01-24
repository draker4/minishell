/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/24 20:09:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	handle_pipe(t_exec *exec, int *i)
{
	pipe(exec->fd_pipe);
	printf("i = %d\n", *i);
	exec->data->pid[*i] = fork();
	if (exec->data->pid[*i] < 0)
		return (perror("Handle_pipe - Fork: "));
	else if (!exec->data->pid[*i])
	{
		if (close(exec->fd_pipe[0]))
			return (perror("Handle_pipe (exec) - Close"), exit (1));
		if (dup2(exec->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Handle_pipe (exec) - Dup2"), exit (1));
		execute_commande(exec);
	}
	else
	{
		g_exit_status = 0;
		if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
			return (perror("Handle_pipe (next) - Dup2"));
		if (close(exec->fd_pipe[1]))
			return (perror("Handle_pipe (next) - Close"));
		printf("i = fin %d\n", *i);
	}
}

static void	last_cmd(t_exec *exec, int *i)
{
	int	j;

	exec->data->pid[*i] = fork();
	if (exec->data->pid[*i] < 0)
		return (perror("Last_commande - Fork"));
	else if (!exec->data->pid[*i])
		execute_commande(exec);
	else
	{
		j = 0;
		while (j <= *i)
			waitpid(exec->data->pid[j++], &g_exit_status, 0);
		g_exit_status = WEXITSTATUS(g_exit_status);
		// printf("g_exit = %d\n", g_exit_status);
	}
}

void	handle_cmd_list(t_exec *exec, int *i)
{
	//ici fonction parse $?
	if (exec->input)
	{
		if (change_input(exec->input))
		{
			close_file(exec);
			if (exec->next)
			{
				*i += 1;
				handle_cmd_list(exec->next, i);
			}
			return ;
		}
	}
	if (exec->output)
	{
		if (change_output(exec->output))
			return (close_file(exec));
	}
	if (exec->next)
	{
		handle_pipe(exec, i);
		close_file(exec);
		*i += 1;
		return (handle_cmd_list(exec->next, i));
	}
	last_cmd(exec, i);
	close_file(exec);
}

void	handle_cmd(t_exec *exec, int *i)
{
	//ici fonction parse $?
	if (exec->input)
		if (change_input(exec->input))
			return (close_file(exec));
	if (exec->output)
		if (change_output(exec->output))
			return (close_file(exec));
	if (exec->cmd == builtin)
		return (execute_builtin(exec));
	else
		last_cmd(exec, i);
	close_file(exec);
}
