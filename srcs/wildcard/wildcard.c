/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 19:18:26 by bperriol         ###   ########lyon.fr   */
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

int	copy_wildcard(char *str, DIR *dirp, t_wild **wild)
{
	t_wild			*new;
	struct dirent	*file;

	file = readdir(dirp);
	while (file)
	{
		if ((str && str[0] != '.' && file->d_name[0] != '.')
			|| (str && str[0] == '.' && file->d_name[0] == '.'))
		{
			new = new_wild(file->d_name);
			if (!new)
				return (wild_clear_data(wild), closedir(dirp), FAIL);
			wild_add_back(wild, new);
		}
		file = readdir(dirp);
	}
	closedir(dirp);
	return (0);
}

char	*link_wildcard(char *str, t_wild **wild)
{
	char	*final;
	t_wild	*tmp;

	tmp = *wild;
	final = NULL;
	while (tmp)
	{
		if (tmp->keep)
		{
			final = wildcard_strjoin(final, tmp->arg);
			if (!final)
				return (str);
		}
		tmp = tmp->next;
	}
	wild_clear_data(wild);
	if (!final)
		return (str);
	return (free(str), final);
}

char	*get_wildcard(char *str)
{
	DIR		*dirp;
	t_wild	*wild;
	char	*check;

	dirp = opendir(".");
	if (!dirp)
		return (perror("get_wildcard - opendir"), str);
	wild = NULL;
	if (copy_wildcard(str, dirp, &wild) || !wild)
		return (str);
	check = check_str(str);
	if (!check)
		return (wild_clear_data(&wild), str);
	check_wildcard(check, wild);
	free(check);
	return (link_wildcard(str, &wild));
}
