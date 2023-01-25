/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 10:26:47 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_cd(t_exec *exec)
{
	exec->data->modify_env = 1;
	if (size_arg(exec->arg) == 1)
	{
		if (!in_env(exec->data->env, "HOME"))
			write(2, "HOME not set\n", 13);
		else if (chdir(in_env(exec->data->env, "HOME")->value))
			perror("Ft_cd - chdir");
		else
			change_var(exec);
		if (!exec->data->pid[exec->nb])
			exit(1);
		return ;
	}
	if (chdir(exec->arg[1]))
	{
		perror("Ft_cd - chdir");
		if (!exec->data->pid[exec->nb])
			exit(1);
		return ;
	}
	else
		change_var(exec);
	if (!exec->data->pid[exec->nb])
		exit(0);
}
