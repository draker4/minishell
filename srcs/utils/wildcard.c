/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 14:09:33 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wildcard_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (free(s1), perror("Gnl_strjoin - Malloc"), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	if (i > 0)
		new[i++] = ' ';
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

char	*get_wildcard(void)
{
	DIR				*dirp;
	char			*wildcard;
	struct dirent	*file;

	dirp = opendir(".");
	wildcard = NULL;
	file = readdir(dirp);
	while (file)
	{
		wildcard = wildcard_strjoin(wildcard, file->d_name);
		file = readdir(dirp);
	}
	printf("%s\n", wildcard);
	closedir(dirp);
	return (wildcard);
}
