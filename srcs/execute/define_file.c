/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/27 14:38:49 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	change_delimiter(t_redir *redir, t_exec *exec, int status)
{
	char	*line;

	g_exit_status = -1;
	redir->file = open(".delimiter_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (redir->file < 0)
		return (perror("Change_delimiter - Open"), FAIL);
	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(exec->save_stdin, &line, exec, status))
			return (FAIL);
		if (confirm_end(redir->str, line))
			break ;
		write(redir->file, line, ft_strlen(line));
		free (line);
	}
	if (line)
		free(line);
	close(redir->file);
	redir->file = open(".delimiter_tmp", O_RDONLY, 0644);
	if (redir->file < 0)
		return (unlink(".delimiter_tmp"),
			perror("Change_delimiter - Open"), FAIL);
	return (0);
}

static int	control_delimiter(t_redir *redir, t_exec *exec)
{
	int	status;

	exec->data->term.c_lflag = exec->data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(exec->save_stdin, TCSANOW, &exec->data->term))
		return (perror("Control_delimiter - tcsetattr"), FAIL);
	status = g_exit_status;
	if (change_delimiter(redir, exec, status))
		return (g_exit_status = status, FAIL);
	g_exit_status = status;
	exec->data->term.c_lflag = exec->data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(exec->save_stdin, TCSANOW, &exec->data->term))
		return (perror("Control_delimiter - tcsetattr"), FAIL);
	return (0);
}

static int	change_input(t_redir *redir, t_exec *exec)
{
	t_redir	*tmp;

	tmp = redir->next;
	if (redir->type == in_file)
	{
		if (access(redir->str, F_OK))
			return (ft_auto_perror("minishell", redir->str, NULL), FAIL);
		redir->file = open(redir->str, O_RDONLY);
		if (redir->file < 0)
			return (perror("Change_input - Open"), FAIL);
	}
	else if (redir->type == delimiter && control_delimiter(redir, exec))
		return (FAIL);
	if (dup2(redir->file, STDIN_FILENO) < 0)
		return (perror("Change_input - Dup2"), FAIL);
	return (0);
}

static int	change_output(t_redir *redir)
{
	if (redir->type == out_file)
		redir->file = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == append)
		redir->file = open(redir->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->file < 0)
		return (ft_auto_perror("minishell", redir->str, NULL), FAIL);
	if (dup2(redir->file, STDOUT_FILENO) < 0)
		return (perror("Change_output - Dup2"), FAIL);
	return (0);
}

int	change_redir(t_exec *exec)
{
	t_redir	*tmp;

	tmp = exec->redir;
	while (tmp)
	{
		if ((tmp->type == in_file || tmp->type == out_file) \
		&& has_space(tmp->str))
		{
			ft_man_perror("minishell: $", find_var(exec, tmp->str),
				": ambiguous redirect");
			return (g_exit_status = 1, close_file(exec), FAIL);
		}
		if ((tmp->type == in_file || tmp->type == delimiter) && \
		change_input(tmp, exec))
			return (g_exit_status = 1, close_file(exec), FAIL);
		if ((tmp->type == out_file || tmp->type == append) && \
		change_output(tmp))
			return (g_exit_status = 1, close_file(exec), FAIL);
		tmp = tmp->next;
	}
	return (0);
}
