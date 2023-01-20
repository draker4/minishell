/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/20 10:56:33 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_cmd_path(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	new[i++] = '/';
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

void	execute_commande(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->arg && exec->arg[i])
		printf("%s\n", exec->arg[i++]);
	i = 0;
	if (ft_strchr(exec->function, '/'))
	{
		execve(exec->function, exec->arg, exec->data->envp);
		return (perror("Execute_commande - Execution (Path)"));
	}
	while (exec->data->path[i])
	{
		exec->cmd_path = join_cmd_path(exec->data->path[i++],
				exec->function);
		if (!exec->cmd_path)
			return (perror("Execute_commande - Join_cmd_path"));
		execve(exec->cmd_path, exec->arg, exec->data->envp);
	}
	return (perror("Execute_commande - Execution (no path)"));
}

void	handle_pipe(t_exec *exec)
{
	pipe(exec->fd_pipe);
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("Fork: "));
	if (!exec->pid)
	{
		if (dup2(exec->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Handle_pipe (exec) - Dup2"));
		if (close(exec->fd_pipe[0]))
			return (perror("Handle_pipe (exec) - Close"));
		return (execute_commande(exec));
	}
	else
	{
		if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
		{
			close_file(exec);
			return (perror("Handle_pipe (next) - Dup2"));
		}
		if (close(exec->fd_pipe[1]))
		{
			close_file(exec);
			return (perror("Handle_pipe (next) - Close"));
		}
		if (waitpid(exec->pid, &exec->data->exit_status, 0) == -1)
		{
			close_file(exec);
			return (perror("Handle_pipe (next) - Waitpid"));
		}
		close_file(exec);
		return (handle_commande(exec->next));
	}
}

void	last_commande(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid < 0)
		return (perror("Last_commande - Fork"));
	else if (!exec->pid)
		execute_commande(exec);
	else
		if (waitpid(exec->pid, &exec->data->exit_status, 0) == -1)
			perror("Last_commande - Waitpid");
}

void	handle_commande(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->input)
	{
		if (change_input(exec, exec->input))
		{
			if (exec->next)
				return (handle_commande(exec->next));
			return ;
		}
	}
	if (exec->output)
		if (change_output(exec, exec->output))
			return ;
	if (exec->next)
		return (handle_pipe(exec));
	if (exec->function)
		last_commande(exec);
	close_file(exec);
}
