/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 13:30:30 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_open_redirect(char *fd, t_pipe *pipe, int redirect)
{
	if (redirect == INFILE)
	{
		if (access(fd, F_OK))
			return (perror("Error"), FAIL);
		pipe->infile = open(fd, O_RDONLY);
		if (pipe->infile < 0)
			return (perror("Error"), FAIL);
		if (dup2(pipe->infile, STDIN_FILENO) < 0)
			return (perror("Dup2: "), FAIL);
	}
	else if (redirect == OUTFILE)
	{
		pipe->outfile = open(fd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipe->outfile < 0)
			return (perror("Error"), FAIL);
		if (dup2(pipe->outfile, STDOUT_FILENO) < 0)
			return (perror("Dup2: "), FAIL);
	}
	return (0);
}

static int	ft_execute_commande(t_pipe *pipex, char *argv, char **envp)
{
	int	i;
	char 	*tmp[3] = {"awk", "{count++} END {print count}", NULL};

	pipex->path = get_path(envp);
	if (!pipex->path)
		return (FAIL);
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

int	ft_pipex(t_pipe *pipex, char *cmd, char **envp, int input)
{
	pipe(pipex->fd_pipe);
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (perror("Fork: "), FAIL);
	if (!pipex->pid)
	{
		if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) < 0)
			return (perror("Dup2: "), FAIL);
		if (close(pipex->fd_pipe[0]))
			return (perror("Close: "), FAIL);
		if (input == STDIN_FILENO)
			exit (FAIL);
		ft_execute_commande(pipex, cmd, envp);
		exit (FAIL);
	}
	else
	{
		if (dup2(pipex->fd_pipe[0], STDIN_FILENO) < 0)
			return (perror("Dup2: "), FAIL);
		if (close(pipex->fd_pipe[1]))
			return (perror("Close: "), FAIL);
		if (waitpid(pipex->pid, NULL, 0) == -1)
			return (perror("Waitpid: "), FAIL);
	}
	return (0);
}

int	execute_line(t_exec exec)
{
	if (!exec)
		return (FAIL);
	
}
