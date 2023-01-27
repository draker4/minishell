/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/27 11:50:50 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(t_check *check, char *arg)
{
	int	i;
	int	j;

	i = check->s_end - 1;
	j = ft_strlen(arg) - 1;
	while (i >= 0 && j >= 0 && check->end[i] == arg[j])
	{
		i--;
		j--;
	}
	if (i < 0)
		return (0);
	return (1);
}

int	check_search(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (0);
	return (1);
}

void	define_index(t_check *check, t_wild *wild, t_index *i, t_index *max)
{
	i->tab = 0;
	i->arg = 0;
	if (check->start)
	{
		i->tab++;
		i->arg = check->s_start;
	}
	max->tab = check->s_tab;
	max->arg = ft_strlen(wild->arg);
	if (check->end)
	{
		max->tab -= 1;
		max->arg -= check->s_end;
	}
}

int	confirm_middle(t_check	*check, t_wild *wild)
{
	t_index	i;
	t_index	max;

	define_index(check, wild, &i, &max);
	while (i.tab < max.tab && i.arg < max.arg)
	{
		if (!check_search(check->tab[i.tab], &wild->arg[i.arg]))
		{
			i.arg += ft_strlen(check->tab[i.tab]);
			i.tab++;
		}
		else
			i.arg++;
	}
	if (i.tab == max.tab)
		return (0);
	return (1);
}

void	wild_check(t_check	*check, t_wild *wild)
{
	if (wild)
	{	
		if (check->start && check_search(check->start, wild->arg))
			return (wild_check(check, wild->next));
		if (check->end && check_end(check, wild->arg))
			return (wild_check(check, wild->next));
		if (check->nb > 1)
			if (confirm_middle(check, wild))
				return (wild_check(check, wild->next));
		wild->keep = 1;
		return (wild_check(check, wild->next));
	}
}
