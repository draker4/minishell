/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:53:43 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 12:01:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	add_char_exit(char *str, char **copy, char *nb_itoa)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			j = 0;
			while (nb_itoa[j])
			{
				*copy = str_add(*copy, nb_itoa[j++]);
				if (!*copy)
					return (perror("Add_char_exit - str_add"), 0);
			}
			i += 2;
		}
		else
		{
			*copy = str_add(*copy, str[i++]);
			if (!*copy)
				return (perror("Add_char_exit - str_add"), 0);
		}
	}
	return (1);
}

char	*parse_exit_status(char *str)
{
	char	*copy;
	char	*nb_itoa;

	nb_itoa = ft_itoa(g_exit_status);
	if (!nb_itoa)
		return (perror("Parse_exit_status - ft_itoa"), NULL);
	copy = malloc(sizeof(char) * 1);
	if (!copy)
		return (perror("Parse_exit_status - malloc"), NULL);
	copy[0] = '\0';
	if (!add_char_exit(str, &copy, nb_itoa))
		return (free(nb_itoa), NULL);
	free(str);
	free(nb_itoa);
	return (copy);
}

int	change_exit_status(t_exec *exec)
{
	int		i;
	char	*str;

	i = -1;
	while (exec->arg && exec->arg[++i])
	{
		if (has_exit_status(exec->arg[i]))
		{
			str = parse_exit_status(exec->arg[i]);
			if (!str)
				return (0);
			exec->arg[i] = str;
		}
	}
	if (exec->function && has_exit_status(exec->function))
	{
		str = parse_exit_status(exec->function);
		if (!str)
			return (0);
		exec->function = str;
	}
	if (!exit_status_redir(exec))
		return (0);
	return (1);
}
