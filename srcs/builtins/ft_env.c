/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 20:06:12 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_env(t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	while (exec->data->envp[i])
// 	{
// 		if (has_equal(exec->data->envp[i]))
// 		{
// 			write(1, exec->data->envp[i], ft_strlen(exec->data->envp[i]));
// 			write(1, "\n", 1);
// 		}
// 		i++;
// 	}
// 	if (!exec->pid)
// 		exit(0);
// }
