/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 11:11:10 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	change_delimiter(t_input *input, t_exec *exec)
{
	char	*line;

	line = NULL;
	input->file = open(".delimiter_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input->file < 0)
		return (perror("Change_delimiter - Open"), FAIL);
	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(0, &line, exec))
		{
			close(input->file);
			unlink(".delimiter_tmp");
			return (FAIL);
		}
		if (confirm_end(input->str, line))
			break ;
		write(input->file, line, ft_strlen(line));
		free (line);
	}
	close(input->file);
	input->file = open(".delimiter_tmp", O_RDONLY, 0644);
	return (0);
}

int	change_input(t_input *input, t_exec *exec)
{
	if (input->in == in_file)
	{
		if (access(input->str, F_OK))
			return (ft_auto_perror("minishell", input->str, NULL), FAIL);
		input->file = open(input->str, O_RDONLY);
		if (input->file < 0)
			return (perror("Change_input - Open"), FAIL);
	}
	else if (input->in == delimiter)
		if (change_delimiter(input, exec))
			return (FAIL);
	if (dup2(input->file, STDIN_FILENO) < 0)
		return (perror("Change_input - Dup2"),
			unlink(".delimiter_tmp"), FAIL);
	if (input->next)
	{
		unlink(".delimiter_tmp");
		return (change_input(input->next, exec));
	}
	return (0);
}

int	change_output(t_output *output)
{
	if (output->out == out_file)
		output->file = open(output->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (output->out == append)
		output->file = open(output->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (output->file < 0)
		return (perror("Change_output - Open"), FAIL);
	if (dup2(output->file, STDOUT_FILENO) < 0)
		return (perror("Change_output - Dup2"), FAIL);
	if (output->next)
		return (change_output(output->next));
	return (0);
}
