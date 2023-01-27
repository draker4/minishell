/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:57:34 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 14:13:41 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_min(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

void	is_built_in(t_exec	*exec)
{
	if (!exec->function || !exec->arg)
	{
		exec->cmd = null;
		return ;
	}
	ft_min(exec->function);
	if (!ft_strncmp(exec->function, "echo", 5) \
	|| !ft_strncmp(exec->function, "cd", 3) \
	|| !ft_strncmp(exec->function, "pwd", 4) \
	|| !ft_strncmp(exec->function, "export", 6) \
	|| !ft_strncmp(exec->function, "unset", 6) \
	|| !ft_strncmp(exec->function, "env", 4) \
	|| !ft_strncmp(exec->function, "exit", 5))
		exec->cmd = builtin;
	else
		exec->cmd = path;
}
