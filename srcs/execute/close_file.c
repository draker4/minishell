/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 10:43:29 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_file(t_exec *exec)
{
	t_redir	*tmp;

	tmp = exec->redir;
	while (tmp)
	{
		if (close(tmp->file))
			perror("close_file");
		if (tmp->type == delimiter)
			unlink(".delimiter_tmp");
		tmp = tmp->next;
	}
}
