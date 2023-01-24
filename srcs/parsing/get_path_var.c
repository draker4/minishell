/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:05:10 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 10:28:26 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_double(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free (str);
}

static int	ft_divide(char const *s, char c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		j = i;
		while (s[i] != c && s[i])
			i ++;
		if (i - j)
			size++;
		if (s[i])
			i++;
	}	
	return (size);
}

static int	ft_insert(const char *s, char c, char **split, int i)
{
	int		j;
	int		k;
	int		l;

	k = 0;
	while (s[i])
	{
		j = i;
		while (s[i] != c && s[i])
			i++;
		if (i - j)
		{
			split[k] = malloc(sizeof(**split) * (i - j + 1));
			if (!split[k])
				return (perror("ft_insert"), ft_free_double(split, k), FAIL);
			l = 0;
			while (j < i)
				split[k][l++] = s[j++];
			split[k][l] = '\0';
			k++;
		}
		if (s[i])
			i++;
	}
	return (0);
}

int	ft_split_data(char ***new, char const *s, char c)
{
	int		size;

	if (s == NULL)
		return (FAIL);
	size = ft_divide(s, c);
	*new = malloc(sizeof(char *) * (size + 1));
	if (*new == NULL)
		return (perror("ft_split_data"), FAIL);
	if (ft_insert(s, c, *new, 0))
		return (FAIL);
	(*new)[size] = NULL;
	return (0);
}

int	get_path(t_data *data)
{
	int		i;
	char	**path_all;

	i = 0;
	if (!data->envp[0])
		return (0);
	while (data->envp[i])
	{
		if (!ft_strncmp("PATH=", data->envp[i], 5))
			break ;
		i++;
	}
	if (!data->envp[i])
		return (0);
	if (ft_split_data(&path_all, data->envp[i], '='))
		return (FAIL);
	if (ft_split_data(&data->path, path_all[1], ':'))
		return (FAIL);
	return (0);
}
