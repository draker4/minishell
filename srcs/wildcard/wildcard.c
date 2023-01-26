/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 21:03:59 by bboisson         ###   ########lyon.fr   */
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

void	check_wildcard(char *str, t_wild *wild, int nb)
{
	int	str_size;
	int	arg_size;

	if (wild)
	{	
		str_size = ft_strlen(str) - 1;
		arg_size = ft_strlen(wild->arg) - 1;
		//printf("%s\n", wild->arg);
		if (str[0] != '*' && str[0] != wild->arg[0])
			return (check_wildcard(str, wild->next, nb));
		//printf("%s\n", wild->arg);
		if (str[str_size] != '*' && str[str_size] != wild->arg[arg_size])
			return (check_wildcard(str, wild->next, nb));
		//printf("%s\n", wild->arg);
		if (nb > 1)
			if (confirm_middle(wild, ft_split(str, '*')))
				return (check_wildcard(str, wild->next, nb));
		//printf("%s\n", wild->arg);
		wild->keep = 1;
		return (check_wildcard(str, wild->next, nb));
	}
}

char	*get_wildcard(char *str)
{
	DIR		*dirp;
	t_wild	*wild;
	char	*check;
	int		nb;

	dirp = opendir(".");
	if (!dirp)
		return (perror("get_wildcard - opendir"), str);
	wild = NULL;
	if (copy_wildcard(str, dirp, &wild) || !wild)
		return (str);
	check = check_str(str);
	if (!check)
		return (wild_clear_data(&wild), str);
	nb = nb_wildcard(str);
	check_wildcard(check, wild, nb);
	free(check);
	return (link_wildcard(str, &wild));
}
