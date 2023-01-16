/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/29 15:25:17 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_get_octet_size(int c)
{
	int	i;

	i = 0;
	while (c / 2)
	{
		c /= 2;
		i++;
	}
	return (i);
}

void	ft_get_octet(int c, int *nb, int *i)
{
	if (c > 0)
		ft_get_octet(c / 2, nb, i);
	nb[*i] = c % 2;
	*i += 1;
}

unsigned char	ft_back_to_char(int *nb)
{
	int	i;
	int	total;
	int	tmp;

	i = 0;
	while (i < 4)
	{
		tmp = nb[i];
		nb[i] = nb[4 + i];
		nb[4 + i] = tmp;
		i++;
	}
	i = 0;
	total = 0;
	while (i < 8)
	{
		total = total * 2 + nb[i];
		i++;
	}
	return (total);
}

unsigned char	ft_swap_bits(char octet)
{
	int	i;
	int	nb[8];

	i = 0;
	while (i < 8)
		nb[i++] = 0;
	i = 6 - ft_get_octet_size(octet);
	ft_get_octet(octet, nb, &i);
	return (ft_back_to_char(nb));
}
