/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/21 16:48:40 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_exec *exec)
{
	int	i;
	int	size;
	int	new_line;

	size = size_arg(exec->arg);
	if (size == 1)
		return (printf("\n"), exit(0));
	i = 1;
	new_line = 1;
	if (!ft_strncmp(exec->arg[1], "-n", 2) && !exec->arg[1][2])
	{
		new_line = 0;
		i++;
	}
	while (exec->arg[i])
	{
		printf("%s", exec->arg[i]);
		if (exec->arg[++i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	exit(0);
}
