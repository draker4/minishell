/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:53:43 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 10:17:37 by bperriol         ###   ########lyon.fr   */
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

char	*parse_exit_status(char *str, int status)
{
	char	*copy;
	char	*nb_itoa;

	nb_itoa = ft_itoa(status);
	if (!nb_itoa)
		return (perror("Parse_exit_status - ft_itoa"), NULL);
	copy = malloc(sizeof(char) * 1);
	if (!copy)
		return (perror("Parse_exit_status - malloc"), NULL);
	copy[0] = '\0';
	if (!add_char_exit(str, &copy, nb_itoa))
		return (free(nb_itoa), free(copy), NULL);
	free(str);
	free(nb_itoa);
	return (copy);
}

static int	change_function_exit_var(t_exec *current)
{
	char	*str;

	if (current->function && has_exit_status(current->function))
	{
		str = parse_exit_status(current->function, g_exit_status);
		if (!str)
			return (0);
		current->function = str;
	}
	return (1);
}

int	change_exit_status(t_exec **exec)
{
	t_exec	*current;
	int		i;
	char	*str;

	current = *exec;
	while (current)
	{
		i = 0;
		while (current->arg[i])
		{
			if (has_exit_status(current->arg[i]))
			{
				str = parse_exit_status(current->arg[i], g_exit_status);
				if (!str)
					return (0);
				current->arg[i] = str;
			}
			i++;
		}
		if (!change_function_exit_var(current) || !exit_status_redir(current))
			return (0);
		g_exit_status = 0;
		current = current->next;
	}
	return (1);
}
