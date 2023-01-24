/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 16:07:54 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_var(char ***env_var, int size)
{
	int		i;
	int		j;
	char	**tmp;

	i = 1;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strncmp(env_var[j][0], env_var[i][0],
			ft_strlen(env_var[j][0])) > 0)
			{
				tmp = env_var[j];
				env_var[j] = env_var[i];
				env_var[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_var(char ***env_var)
{
	int		i;
	int		j;

	i = 0;
	while (env_var[i])
	{
		j = 0;
		if (!(env_var[i][j][0] == '_' && !env_var[i][j][1]))
		{
			printf("declare -x %s", env_var[i][j]);
			if (env_var[i][++j])
			{
				printf("=\"");
				while (env_var[i][j])
					printf("%s", env_var[i][j++]);
				printf("\"");
			}
			printf("\n");
		}
		i++;
	}
}

void	print_export(t_exec *exec)
{
	int		i;
	char	***env_var;

	env_var = malloc(sizeof(char **) * (size_arg(exec->data->envp) + 1));
	if (!env_var)
		return (perror("ft_export"));
	i = 0;
	while (exec->data->envp[i])
	{
		env_var[i] = ft_split(exec->data->envp[i], '=');
		i++;
	}
	env_var[i] = NULL;
	sort_env_var(env_var, i);
	print_env_var(env_var);
	if (!exec->pid)
		exit(0);
}
