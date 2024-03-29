/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 19:39:01 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// strjoin with the s1 being free at the end;
static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (free(s1), perror("Gnl_strjoin - Malloc"), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}

int	parse_line_delimiter(char **line, t_exec *exec, int status)
{
	char	*parsed_line;

	parsed_line = parse_env_del(*line, exec->data->envp);
	if (!parsed_line)
		return (FAIL);
	free(*line);
	*line = parsed_line;
	parsed_line = parse_exit_status(*line, status);
	if (!parsed_line)
		return (FAIL);
	*line = parsed_line;
	return (0);
}

int	get_delimiter(char **line, t_exec *exec)
{
	char	str[2];
	int		nbc;

	*line = NULL;
	nbc = 1;
	str[0] = '\0';
	while (!ft_strchr(str, '\n') && nbc > 0)
	{
		nbc = read(exec->save_stdin, str, 1);
		if (nbc < 0)
			return (free(*line), FAIL);
		str[nbc] = '\0';
		*line = gnl_strjoin(*line, str);
		if (!*line)
			return (FAIL);
	}
	return (0);
}

int	confirm_end(char *s1, char *s2)
{
	int		i;
	int		size_s1;
	int		size_s2;

	if (!*s2)
		return (1);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (size_s1 != size_s2 - 1)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (i == size_s1 && s2[i] == '\n')
		return (1);
	return (0);
}

int	write_in_delimiter_file(t_redir *redir, t_exec *exec, int status)
{
	char	*line;

	while (1)
	{
		write(1, " > ", 3);
		if (get_delimiter(&line, exec))
			return (fd_error(exec), FAIL);
		if (confirm_end(redir->str, line))
			break ;
		if (!redir->modif && parse_line_delimiter(&line, exec, status))
			return (free(line), FAIL);
		write(exec->infile, line, ft_strlen(line));
		free (line);
	}
	if (line)
		free(line);
	return (0);
}
