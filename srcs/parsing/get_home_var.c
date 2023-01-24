/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:05:10 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 12:00:48 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_home(t_data *data)
{
	int		i;
	char	**path_home;

	i = 0;
	if (!data->envp[0])
		return (0);
	while (data->envp[i])
	{
		if (!ft_strncmp("HOME=", data->envp[i], 5))
			break ;
		i++;
	}
	if (!data->envp[i])
		return (0);
	if (ft_split_data(&path_home, data->envp[i], '='))
		return (FAIL);
	if (size_arg(path_home) != 2)
		return (write(2, "HOME error\n", 11), FAIL);
	data->home = path_home[1];
	return (0);
}
