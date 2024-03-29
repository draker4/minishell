/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 15:49:10 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	change_delimiter(t_exec *exec, t_redir *redir, int status)
{
	g_exit_status = -1;
	exec->delimfile = 1;
	exec->infile = open(".delimiter_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->infile < 0)
		return (perror("change_delimiter - Open"), fd_error(exec), FAIL);
	if (write_in_delimiter_file(redir, exec, status))
		return (FAIL);
	close(exec->infile);
	exec->infile = open(".delimiter_tmp", O_RDONLY, 0644);
	if (exec->infile < 0)
		return (perror("change_delimiter - Open"), fd_error(exec), FAIL);
	return (0);
}

static int	control_delimiter(t_exec *exec, t_redir *redir)
{
	int	status;

	exec->data->term.c_lflag = exec->data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(exec->save_stdin, TCSANOW, &exec->data->term))
		return (perror("Control_delimiter - tcsetattr"), FAIL);
	status = g_exit_status;
	if (change_delimiter(exec, redir, status))
		return (g_exit_status = status, FAIL);
	g_exit_status = status;
	exec->data->term.c_lflag = exec->data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(exec->save_stdin, TCSANOW, &exec->data->term))
		return (perror("Control_delimiter - tcsetattr"), FAIL);
	return (0);
}

static void	change_input(t_exec *exec, t_redir *redir)
{
	close_infile(exec);
	if (redir->type == in_file)
	{
		if (access(redir->str, F_OK))
			return (file_error(exec, redir));
		exec->infile = open(redir->str, O_RDONLY);
		if (exec->infile < 0)
			return (perror("Change_input - Open"), fd_error(exec));
	}
	else if (redir->type == delimiter && control_delimiter(exec, redir))
		return ;
	if (dup2(exec->infile, STDIN_FILENO) < 0)
		return (perror("Change_input - Dup2"), fd_error(exec));
	return (change_redir(exec, redir->next));
}

static void	change_output(t_exec *exec, t_redir	*redir)
{
	close_outfile(exec);
	if (redir->type == out_file)
		exec->outfile = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == append)
		exec->outfile = open(redir->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (exec->outfile < 0)
		return (file_error(exec, redir));
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		return (perror("Change_output - Dup2"), fd_error(exec));
	return (change_redir(exec, redir->next));
}

void	change_redir(t_exec *exec, t_redir	*redir)
{
	if (!redir)
		return ;
	if (redir->ambiguous)
	{
		ft_man_perror("minishell: ", redir->str,
			": ambiguous redirect");
		g_exit_status = 1;
		exec->file_error = 1;
		return ;
	}
	else if ((redir->type == in_file || redir->type == delimiter))
		return (change_input(exec, redir));
	else if ((redir->type == out_file || redir->type == append))
		return (change_output(exec, redir));
}
