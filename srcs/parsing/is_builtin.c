/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:57:34 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/20 03:20:36 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_built_in(t_exec	*exec)
{
	char	*str;

	str = exec->function;
	if (!str || !exec->arg)
	{
		exec->cmd = null;
		return ;
	}
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3) \
	|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 6) \
	|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4) \
	|| !ft_strncmp(str, "exit", 5))
		exec->cmd = builtin;
	else
		exec->cmd = path;
}
