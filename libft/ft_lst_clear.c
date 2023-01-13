/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/28 18:38:33 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content)
{
	free (content);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del (lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*clear;
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	clear = *lst;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		ft_lstdelone (tmp, del);
	}
	*lst = NULL;
}
