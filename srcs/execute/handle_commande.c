/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commande.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 17:47:08 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*ft_join_cmd_path(char const *s1, char const *s2)
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
	if (exec->data->path)
		return (perror("ft_execute_fonction - Path: "));
	pipex->cmd = ft_split(argv, ' ');
	if (!pipex->cmd)
		return (perror("Path: "), FAIL);
	i = 0;
	if (ft_strchr(pipex->cmd[0], '/'))
	{
		pipex->cmd[0] = ft_strrchr(pipex->cmd[0], '/');
		printf("%s", pipex->cmd[0]);
		execve(argv, pipex->cmd, envp);
		return (perror("Execution: "), FAIL);
	}
	while (pipex->path[i])
	{
		pipex->cmd_path = ft_join_cmd_path(pipex->path[i++], pipex->cmd[0]);
		if (!pipex->cmd_path)
			return (perror("Cmd_path: "), FAIL);
		if (!ft_strncmp(pipex->cmd[0], "awk", 3))
			execve(pipex->cmd_path, tmp, envp);
		execve(pipex->cmd_path, pipex->cmd, envp);
	}
	return (perror("Execution: "), FAIL);
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
			return (perror("Handle_pipe (main) - Dup2: "));
		if (close(exec->fd_pipe[0]))
			return (perror("Handle_pipe (main) - Close: "));
		return (execute_commande(exec));
	}
	else
	{
		if (dup2(exec->fd_pipe[0], STDIN_FILENO) < 0)
			return (perror("Handle_pipe (next) - Dup2: "));
		if (close(exec->fd_pipe[1]))
			return (perror("Handle_pipe (next) - Close: "));
		if (waitpid(exec->pid, &exec->status, 0) == -1)
			return (perror("Handle_pipe (next) - Waitpid: "));
		return (handle_commande(exec->next));
	}
}

void	handle_commande(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->input)
	{
		if (change_input(exec, exec.input))
		{
			if (exec->next)
				return (handle_commande(exec->next));
			return ;
		}
	}
	if (exec->output)
		if (change_output(exec, exec.output))
			return ;
	if (exec->next)
		return (handle_pipe(exec));
	execute_fonction(exec);
}
