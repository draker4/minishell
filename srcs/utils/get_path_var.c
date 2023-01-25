/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:05:10 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 17:33:48 by bperriol         ###   ########lyon.fr   */
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
			i++;
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

static char	**split_data(char const *s, char c)
{
	int		size;
	char	**split;

	if (s == NULL)
		return (NULL);
	size = ft_divide(s, c);
	split = malloc(sizeof(char *) * (size + 1));
	if (split == NULL)
		return (perror("ft_split_data - malloc"), NULL);
	if (ft_insert(s, c, split, 0))
		return (NULL);
	split[size] = NULL;
	return (split);
}

int	get_path(t_data *data)
{
	if (in_env(data->env, "PATH") && in_env(data->env, "PATH")->value)
	{
		data->path = split_data(in_env(data->env, "PATH")->value, ':');
		if (!data->path)
			return (FAIL);
	}
	else
		data->path = NULL;
	return (0);
}
