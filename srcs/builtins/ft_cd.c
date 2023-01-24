/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 12:01:05 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_exec *exec)
{
	if (size_arg(exec->arg) == 1)
	{
		if (!exec->data->home)
		{
			write(2, "HOME not set\n", 13);
			if (!exec->pid)
				exit(1);
		}
		else if (chdir(exec->data->home))
		{
			perror("Ft_cd");
			if (!exec->pid)
				exit(1);
		}
	}
	else if (chdir(exec->arg[1]))
	{
		perror("Ft_cd");
		if (!exec->pid)
			exit(1);
	}
	if (!exec->pid)
		exit(0);
}
