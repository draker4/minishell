/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 15:36:18 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_all(char *str, t_data *data, t_exec **exec)
{
	(void)str;
	(void)data;
	if (!str)
		free(str);
	str = NULL;
	if (data->path)
		free_split(data->path);
	data->path = NULL;
	// if (data->home)
	// 	free(data->home);
	// data->home = NULL;
	exec_clear_data(exec);
}
