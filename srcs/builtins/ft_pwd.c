/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 13:35:42 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_pwd(t_exec *exec)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("Ft_pwd - getcwd");
		g_exit_status = 1;
		if (!exec->data->pid[exec->nb])
			exit(1);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}
