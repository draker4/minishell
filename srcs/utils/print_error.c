/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:32:11 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 16:31:28 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *info, char *ft, char *error)
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
