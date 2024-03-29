/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:18:57 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 14:44:56 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_add(char *str, char c)
{
	int		i;
	char	*copy;

	if (!str)
		return (NULL);
	copy = malloc(sizeof(char) * ((int)ft_strlen(str) + 2));
	if (!copy)
		return (free(str), perror("Str_add: "), NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i++] = c;
	copy[i] = '\0';
	free(str);
	return (copy);
}

char	*create_copy(char *str, int save, int i)
{
	char	*copy;
	int		j;

	copy = malloc(sizeof(char) * (i - save + 1));
	if (!copy)
		return (perror("Create_copy: "), NULL);
	j = 0;
	while (save != i)
		copy[j++] = str[save++];
	copy[j] = '\0';
	return (copy);
}

int	delete_slash_symbol(t_exec *exec, char *str)
{
	int		i;
	int		save;
	char	*function;

	i = 0;
	save = 0;
	while (str[i])
	{
		if (str[i] == '/' && !is_in_quote(str, i, 0) && str[i + 1])
			save = i + 1;
		i++;
	}
	function = create_copy(str, save, i);
	free(exec->arg[0]);
	exec->arg[0] = function;
	return (1);
}

int	size_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}
