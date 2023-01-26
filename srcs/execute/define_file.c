/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 13:37:00 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	confirm_end(const char *s1, const char *s2)
{
	int	i;
	int	size_s1;
	int	size_s2;

	i = 0;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (size_s1 != size_s2 - 1)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (i == size_s1 && s2[i] == '\n')
		return (1);
	return (0);
}

static int	change_delimiter(t_redir *redir, t_exec *exec)
{
	char	*line;

	line = NULL;
	redir->file = open(".delimiter_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (redir->file < 0)
		return (perror("Change_delimiter - Open"), FAIL);
	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(0, &line, exec))
		{
			close(redir->file);
			unlink(".delimiter_tmp");
			return (FAIL);
		}
		if (confirm_end(redir->str, line))
			break ;
		write(redir->file, line, ft_strlen(line));
		free (line);
	}
	close(redir->file);
	redir->file = open(".delimiter_tmp", O_RDONLY, 0644);
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
	else if (redir->type == delimiter)
		if (change_delimiter(redir, exec))
			return (perror("Change_input - access"), FAIL);
	if (dup2(redir->file, STDIN_FILENO) < 0)
		return (perror("Change_input - Dup2"),
			unlink(".delimiter_tmp"), FAIL);
	while (tmp)
	{
		if (tmp->type == in_file || tmp->type == delimiter)
			unlink(".delimiter_tmp");
		tmp = tmp->next;
	}
	return (0);
}

static int	change_output(t_redir *redir)
{
	if (redir->type == out_file)
		redir->file = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == append)
		redir->file = open(redir->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->file < 0)
		return (perror("Change_output - Open"), FAIL);
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
		if (has_space(tmp->str))
		{
			ft_man_perror("minishell: $", find_var(exec, tmp->str),
				": ambiguous redirect");
			// write(2, "minishell: $", 11);
			// write(2, find_var(exec->data->env, tmp->str), \
			// ft_strlen(find_var(exec->data->env, tmp->str)) + 1);
			// write(2, ": ambiguous redirect\n", 21);
			return (g_exit_status = 1, close_file(exec), FAIL);
		}
		if ((tmp->type == in_file || tmp->type == delimiter) && \
		change_input(tmp, exec))
			return (g_exit_status = 1, close_file(exec), FAIL);
		if ((tmp->type == out_file || tmp->type == append) && \
		change_output(tmp))
			return (close_file(exec), FAIL);
		tmp = tmp->next;
	}
	return (0);
}
