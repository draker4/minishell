/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/23 15:01:17 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}
