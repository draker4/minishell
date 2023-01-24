/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 15:52:25 by bperriol         ###   ########lyon.fr   */
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

void	free_all(char *str, t_exec **exec)
{
	if (!str)
		free(str);
	str = NULL;
	exec_clear_data(exec);
}

void	free_data(t_data *data)
{
	if (data->path)
		free_split(data->path);
	if (data->envp)
		free_split(data->envp);
	if (data->env)
		env_clear_data(&data->env);
}
