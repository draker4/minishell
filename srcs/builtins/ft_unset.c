/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 18:20:38 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	not_valid_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	unset_var(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->arg[i])
	{
		if (not_valid_var(exec->arg[i]))
		{
			g_exit_status = 1;
			write(2, "minishell: ", 11);
			write(2, exec->arg[i], ft_strlen(exec->arg[i]));
			write(2, ": not a valid identifier\n", 25);
		}
		else if (in_env(exec->data->env, exec->arg[i]))
			remove_var(&exec->data->env, exec->arg[i]);
		i++;
	}
	if (!exec->data->pid[exec->nb])
		exit(0);
}

void	ft_unset(t_exec *exec)
{
	g_exit_status = 0;
	if (size_arg(exec->arg) == 1)
	{
		if (!exec->data->pid[exec->nb])
			exit(0);
		return ;
	}
	if (exec->arg[1][0] == '_' && !exec->arg[1][1])
	{
		if (!exec->data->pid[exec->nb])
			exit(0);
		return ;
	}
	exec->data->modify_env = 1;
	return (unset_var(exec));
}
