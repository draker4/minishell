/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 17:34:09 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_exec *exec)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("Ft_pwd - getcwd");
		if (!exec->pid)
			exit(1);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	if (!exec->pid)
		exit(0);
}
