/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:32:11 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 15:29:42 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_auto_perror_code(char *info, char *ft, char *error)
{
	if (info)
	{
		write(2, info, ft_strlen(info));
		write(2, ": ", 2);
	}
	if (ft)
	{
		write(2, ft, ft_strlen(ft));
		write(2, ": ", 2);
	}
	if (!error)
		return (perror(NULL), 1);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}

void	ft_auto_perror(char *info, char *ft, char *error)
{
	if (info)
	{
		write(2, info, ft_strlen(info));
		write(2, ": ", 2);
	}
	if (ft)
	{
		write(2, ft, ft_strlen(ft));
		write(2, ": ", 2);
	}
	if (!error)
		return (perror(NULL));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	ft_man_perror(char *info, char *ft, char *error)
{
	if (info)
		write(2, info, ft_strlen(info));
	if (ft)
		write(2, ft, ft_strlen(ft));
	if (!error)
		return (perror(NULL));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
