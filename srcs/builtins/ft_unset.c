/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 15:09:24 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	remove_var(t_exec *exec, char *var)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;

// 	new_env = malloc(sizeof(char *) * (size_arg(exec->data->envp)));
// 	i = 0;
// 	j = 0;
// 	while (exec->data->envp[i])
// 	{
// 		if (ft_strncmp(var, exec->data->envp[i], ft_strlen(var) + 1))
// 			new_env[j++] = exec->data->envp[i];
// 		else
// 			free(exec->data->envp[i]);
// 		i++;
// 	}
// 	new_env[j] = NULL;
// 	exec->data->envp = new_env;
// 	return (1);
// }

// static char	*get_value(char *str)
// {
// 	char	*value;
// 	int		i;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	value = create_copy(str, i + 1, ft_strlen(str));
// 	return (value);
// }

// void	ft_unset(t_exec *exec)
// {
// 	int		i;
// 	int		j;
// 	char	*value;

// 	if (size_arg(exec->arg) == 1)
// 	{
// 		if (!exec->pid)
// 			exit(0);
// 		return ;
// 	}
// 	i = 1;
// 	while (exec->arg[i])
// 	{
// 		j = 0;
// 		while (exec->data->envp && exec->data->envp[j])
// 		{
// 			value = get_value(exec->data->envp[j]);
// 			if (!value)
// 			{
// 				if (!exec->pid)
// 					exit(1);
// 				return ;
// 			}
// 			printf("la\n");
// 			if (!ft_strncmp(getenv(exec->arg[i]), value, ft_strlen(value) + 1))
// 			{
// 				if (!remove_var(exec, exec->data->envp[j]))
// 				{
// 					if (!exec->pid)
// 						exit(1);
// 					return ;
// 				}
// 			}
// 			printf("la\n");
// 			free(value);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (!exec->pid)
// 		exit(0);
// 	return ;
// }

// // void	ft_unset(t_exec *exec)
// // {
// // 	int		i;
// // 	int		j;
// // 	char	*value;

// // 	if (size_arg(exec->arg) == 1)
// // 	{
// // 		if (!exec->pid)
// // 			exit(0);
// // 		return ;
// // 	}
// // 	i = 1;
// // 	while (exec->arg[i])
// // 	{
// // 		if (ft)
// // 	}
// // 	if (!exec->pid)
// // 		exit(0);
// // 	return ;
// // }
