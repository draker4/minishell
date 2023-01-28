/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:09:09 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 15:13:13 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	move_index(char *str, int *i)
{
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	if (str[*i] && str[*i] == '}')
		*i += 1;
	*i -= 1;
}

static int	add_env(char **word_parsed, char **envp, int var)
{
	int	k;

	k = 0;
	while (envp[var][k] != '=')
		k++;
	k++;
	while (envp[var][k])
	{
		*word_parsed = str_add(*word_parsed, envp[var][k]);
		if (!*word_parsed)
			return (0);
		if (envp[var][k] == ' ')
			while (envp[var][k] && envp[var][k] == ' ')
				k++;
		else
			k++;
	}
	return (1);
}

int	check_env(char *str, char **word_parsed, int *i, char **envp)
{
	int	j;
	int	k;
	int	var;

	var = -1;
	if (ft_isdigit(str[*i]))
		return (1);
	if (str[*i] == '{')
		*i += 1;
	j = 0;
	while (envp[j])
	{
		k = 0;
		while (envp[j][k] && envp[j][k] != '=' && str[*i + k] && \
		envp[j][k] == str[*i + k])
			k++;
		if (envp[j][k] == '=' && (!str[*i + k] || str[*i + k] == '}' \
		|| (!ft_isalnum(str[*i + k]) && str[*i + k] != '_')))
			var = j;
		j++;
	}
	move_index(str, i);
	if (var != -1 && !add_env(word_parsed, envp, var))
		return (0);
	return (1);
}

static int	add_env_quotes(char **word_parsed, char **envp, int var)
{
	int	k;

	k = 0;
	while (envp[var][k] != '=')
		k++;
	k++;
	while (envp[var][k])
	{
		*word_parsed = str_add(*word_parsed, envp[var][k]);
		if (!*word_parsed)
			return (0);
		k++;
	}
	return (1);
}

int	check_env_quotes(char *str, char **word_parsed, int *i, char **envp)
{
	int	j;
	int	k;
	int	var;

	var = -1;
	if (ft_isdigit(str[*i]))
		return (1);
	if (str[*i] == '{')
		*i += 1;
	j = 0;
	while (envp[j])
	{
		k = 0;
		while (envp[j][k] && envp[j][k] != '=' && str[*i + k] && \
		envp[j][k] == str[*i + k])
			k++;
		if (envp[j][k] == '=' && (!str[*i + k] || str[*i + k] == '}' \
		|| (!ft_isalnum(str[*i + k]) && str[*i + k] != '_')))
			var = j;
		j++;
	}
	move_index(str, i);
	if (var != -1 && !add_env_quotes(word_parsed, envp, var))
		return (0);
	return (1);
}
