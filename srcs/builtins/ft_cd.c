/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 11:04:37 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	change_var(t_exec *exec)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (perror("Change_var - Getcwd"));
	oldpwd = in_env(exec->data->env, "OLDPWD");
	pwd = in_env(exec->data->env, "PWD");
	if (pwd && oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = buf;
	}
}

void	no_arg(t_exec *exec)
{
	if (!in_env(exec->data->env, "HOME"))
		write(2, "HOME not set\n", 13);
	else if (chdir(in_env(exec->data->env, "HOME")->value))
		perror("Ft_cd - chdir");
	else
		change_var(exec);
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
	return ;
}

void	ft_cd(t_exec *exec)
{
	exec->data->modify_env = 1;
	if (size_arg(exec->arg) == 1)
		return (no_arg(exec));
	if (chdir(exec->arg[1]))
	{
		perror("Ft_cd - chdir");
		g_exit_status = 1;
		if (!exec->data->pid[exec->nb])
			exit(1);
		return ;
	}
	else
		change_var(exec);
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}
