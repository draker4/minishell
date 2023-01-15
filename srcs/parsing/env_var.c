/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:09:09 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/14 03:38:25 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_index(char *str, int *i)
{
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	*i -= 1;
}

static int	add_env(char **line_parsed, char **envp, int var)
{
	int	k;

	k = 0;
	while (envp[var][k] != '=')
		k++;
	k++;
	while (envp[var][k])
	{
		*line_parsed = str_add(*line_parsed, envp[var][k]);
		if (!*line_parsed)
			return (0);
		if (envp[var][k] == ' ')
			while (envp[var][k] && envp[var][k] == ' ')
				k++;
		else
			k++;
	}
	return (1);
}

int	check_env(char *str, char **line_parsed, int *i, char **envp)
{
	int	j;
	int	k;
	int	var;

	var = -1;
	if (ft_isdigit(str[*i]))
		return (1);
	j = 0;
	while (envp[j])
	{
		k = 0;
		while (envp[j][k] && envp[j][k] != '=' && str[*i + k] && \
		envp[j][k] == str[*i + k])
			k++;
		if (envp[j][k] == '=' && (!str[*i + k] || (!ft_isalnum(str[*i + k]) \
		&& str[*i + k] != '_')))
			var = j;
		j++;
	}
	move_index(str, i);
	if (var != -1)
		if (!add_env(line_parsed, envp, var))
			return (0);
	return (1);
}
