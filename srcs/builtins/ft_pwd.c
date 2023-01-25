/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 09:18:55 by bboisson         ###   ########lyon.fr   */
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
		if (!exec->data->pid[exec->nb])
			exit(1);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
	if (!exec->data->pid[exec->nb])
		exit(0);
}
