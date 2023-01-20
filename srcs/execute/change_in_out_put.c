/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in_out_put.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/20 10:30:39 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_delimiter(t_exec *exec, t_input *input)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(0, line))
			return (FAIL);
		if (!ft_strncmp(input->str, line, ft_strlen(input->str) + 1))
		{
			if (input->next)
			{
				free (exec->delimiter);
				exec->delimiter = NULL;
				return (change_input(exec, input->next));
			}
			return (0);
		}
		exec->delimiter = gnl_strjoin(exec->delimiter, line);
		if (!exec->delimiter)
			return (FAIL);
		free (line);
	}
	return (0);
}

int	change_in_file(t_exec *exec, t_input *input)
{
	if (access(input->str, F_OK))
		return (perror("Change_in_file - access"), FAIL);
	input->file = open(input->str, O_RDONLY);
	if (input->file < 0)
		return (perror("Change_in_file - Open"), FAIL);
	exec->infile = input->file;
	if (dup2(exec->infile, STDIN_FILENO) < 0)
		return (perror("Change_in_file - Dup2"), FAIL);
	if (input->next)
		return (change_input(exec, input->next));
	return (0);
}

int	change_input(t_exec *exec, t_input *input)
{
	if (input->in == in_file)
		return (change_in_file(exec, input));
	else if (input->in == delimiter)
		return (change_delimiter(exec, input));
	return (FAIL);
}

int	change_output(t_exec *exec, t_output *output)
{
	if (output->out == out_file)
		output->file = open(output->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (output->out == append)
		output->file = open(output->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (output->file < 0)
		return (perror("Change_output - Open"), FAIL);
	exec->outfile = output->file;
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		return (perror("Change_output - Dup2"), FAIL);
	if (output->next)
		return (change_output(exec, output->next));
	return (0);
}
