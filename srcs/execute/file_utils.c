/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 13:16:13 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	close_infile(t_exec *exec)
{
	if (exec->infile != -1)
	{
		if (close(exec->infile))
			perror("close_file - close infile");
		exec->infile = -1;
	}
	if (exec->delimfile)
	{
		if (unlink(".delimiter_tmp"))
			perror("close_file - unlink delimiter");
		exec->delimfile = 0;
	}
}

void	close_outfile(t_exec *exec)
{
	if (exec->outfile != -1)
	{
		if (close(exec->outfile))
			perror("close_file - close outfile");
		exec->outfile = -1;
	}
}

void	close_file(t_exec *exec)
{
	if (exec->outfile != -1)
		close_outfile(exec);
	if (exec->infile != -1)
		close_infile(exec);
}

void	fd_error(t_exec *exec)
{
	close_file(exec);
	exec->file_error = 1;
	g_exit_status = 1;
	return ;
}

void	file_error(t_exec *exec, t_redir *redir)
{
	close_file(exec);
	exec->file_error = 1;
	g_exit_status = 1;
	ft_auto_perror("minishell", redir->str, NULL);
	return ;
}
