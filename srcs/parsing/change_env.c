/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:28:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 15:53:44 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_ambiguous(t_redir *redir, t_env *full_env, int *i)
{
	int		save;
	char	*copy;
	t_env	*env;

	save = *i;
	while (redir->str[*i] && (ft_isalnum(redir->str[*i]) || \
	redir->str[*i] == '_'))
		*i += 1;
	copy = create_copy(redir->str, save, *i);
	if (!copy)
		return ;
	env = in_env(full_env, copy);
	free(copy);
	if (!env)
	{
		redir->ambiguous = 1;
		return ;
	}
	save = 0;
	while (env->value[save])
	{
		if (env->value[save] == ' ' && !is_in_quote(env->value, save, 0))
			redir->ambiguous = 1;
		save++;
	}
}

static void	ambiguous_redirect(t_redir *redir, t_exec *exec)
{
	int	i;

	i = 0;
	while (redir->str[i])
	{
		if (redir->str[i] == '$' && !is_in_quote(redir->str, i, 0))
		{
			i++;
			if (redir->str[i] && redir->str[i] == '{')
				i++;
			is_ambiguous(redir, exec->data->env, &i);
		}
		if (redir->str[i])
			i++;
	}
}

static int	change_env_redir(t_redir *current, t_exec *exec)
{
	t_redir	*tmp;
	char	*parse_word;

	tmp = current;
	while (tmp)
	{
		if (tmp->type != delimiter)
		{
			ambiguous_redirect(tmp, exec);
			if (!tmp->ambiguous)
			{
				parse_word = parse_env_only(tmp->str, exec->data->envp);
				if (!parse_word)
					return (0);
				free(tmp->str);
				tmp->str = parse_word;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	change_env(t_exec **exec)
{
	t_exec	*current;
	char	*parse_word;
	int		i;

	current = *exec;
	while (current)
	{
		i = 0;
		while (current->arg && current->arg[i])
		{
			parse_word = parse_env_only(current->arg[i], current->data->envp);
			if (!parse_word)
				return (0);
			free(current->arg[i]);
			current->arg[i] = parse_word;
			i++;
		}
		if (!change_env_redir(current->redir, current))
			return (0);
		current = current->next;
	}
	return (1);
}
