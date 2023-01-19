/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_in_out_put.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 17:32:52 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	change_delimiter(t_exec *exec, t_input input)
{
	char	*line;

	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(0, line))
			return (FAIL);
		if (!ft_strncmp(input.file, line, ft_strlen(input.file) + 1))
		{
			if (input.next)
			{
				free (exec.delimiter);
				exec.delimiter = NULL;
				return (change_input(exec, input.next));
			}
			return (0);
		}
		exec.delimiter = gnl_strjoin(exec.delimiter, line);
		if (!exec.delimiter)
			return (FAIL);
		free (line);
	}
	return (0);
}

int	change_in_file(t_exec *exec, t_input input)
{
	if (access(input.char, F_OK))
		return (printf("bash: %s", input.char),
			perror(":"), FAIL);
	exec->infile = open(input.char, O_RDONLY);
	if (exec->infile < 0)
		return (perror("Change_input - Open:"), FAIL);
	if (dup2(exec->infile, STDIN_FILENO) < 0)
		return (perror("Change_input - Dup2: "), FAIL);
	if (input.next)
		return (change_input(exec, input.next));
	return (0);
}

int	change_input(t_exec *exec, t_input input)
{
	if (input.e_in == in_file)
		return (change_in_file(exec, input));
	else if (input.e_in == delimiter)
		return (change_delimiter(exec, input));
	return (FAIL);
}

int	change_output(t_exec *exec, t_output output)
{
	if (output.e_out == out_file)
		exec->outfile = open(output.char, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (output.e_out == append)
		exec->outfile = open(output.char, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (exec->outfile < 0)
		return (perror("Change_output - Open:"), FAIL);
	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
		return (perror("Change_output - Dup2: "), FAIL);
	if (output.next)
		return (change_output(exec, output.next));
	return (0);
}
