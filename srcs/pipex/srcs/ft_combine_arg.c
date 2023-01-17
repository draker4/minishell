/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_combine_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/17 16:45:03 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_join_word(char const *s1, char const *s2, char c)
{
	char	*new;
	int		s1_size;
	int		s2_size;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = 0;
	while (s1[i] && )
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1[j] == c)
		j++;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] && s2[j] != c)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char	**ft_combine_arg(char **argv, char c)
{
	char	**cmd;

	cmd = ft_split(argv, '\'');
	if (cmd)
		return (perror("Path: "), FAIL);
}
