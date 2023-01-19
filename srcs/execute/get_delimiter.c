/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 18:44:40 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (free(s1), perror("Gnl_strjoin - Malloc: "), NULL);
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

static void	reset_str(char *tmp, char *str, size_t start)
{
	size_t	i;

	i = 0;
	while (tmp[start + i])
	{
		str[i] = tmp[start + i];
		i++;
	}
	str[i] = '\0';
}

static int	ret_line(char *tmp, char *str, char *line)
{
	size_t	i;

	i = 0;
	if (tmp[0] == '\0')
		return (free(tmp), 0);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(tmp), perror("Ret_line - Malloc (line): "), FAIL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = tmp[i];
	line[i + 1] = '\0';
	if (tmp[i++] != '\0')
		reset_str(tmp, str, i);
	free(tmp);
	return (0);
}

int	get_delimiter(int fd, char *line)
{
	static char	str[BUFFER_SIZE + 1];
	char		*tmp;
	int			nbc;

	nbc = 1;
	tmp = gnl_strjoin(NULL, str);
	if (!tmp)
		return (FAIL);
	while (!ft_strchr(str, '\n') && nbc > 0)
	{
		nbc = read(fd, str, BUFFER_SIZE);
		if (nbc < 0)
		{
			str[0] = '\0';
			return (free(tmp), perror("Get_next_line - read: "), FAIL);
		}
		str[nbc] = '\0';
		tmp = gnl_strjoin(tmp, str);
		if (!tmp)
			return (FAIL);
	}
	return (ret_line(tmp, str, line));
}
