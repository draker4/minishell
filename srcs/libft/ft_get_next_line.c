/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 13:50:59 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char static	*ft_str_join(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (free(s1), NULL);
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

void static	ft_reset_str(char *tmp, char *str, size_t start)
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

char static	*ft_ret_line(char *tmp, char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (tmp[0] == '\0')
		return (free(tmp), NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(tmp), NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = tmp[i];
	line[i + 1] = '\0';
	if (tmp[i++] != '\0')
		ft_reset_str(tmp, str, i);
	free(tmp);
	return (line);
}

char static	*ft_read_file(int fd, char *str)
{
	char	*tmp;
	int		nbc;

	tmp = NULL;
	nbc = 1;
	if (str[0])
		tmp = ft_str_join(tmp, str);
	while (!ft_strchr(str, '\n') && nbc > 0)
	{
		nbc = read(fd, str, BUFFER_SIZE);
		if (nbc < 0)
		{
			str[0] = '\0';
			return (free(tmp), NULL);
		}
		str[nbc] = '\0';
		tmp = ft_str_join(tmp, str);
	}
	return (ft_ret_line(tmp, str));
}

char	*get_next_line(int fd)
{
	static char	str[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (ft_read_file(fd, str[fd]));
}
