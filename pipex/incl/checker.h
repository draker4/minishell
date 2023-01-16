/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:01:31 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"
# include "push_swap.h"

/* ------------------------------  STRUCTURE  ------------------------------- */

typedef struct s_check
{
	char			*inst;
	struct s_check	*prev;
	struct s_check	*next;
}					t_check;

/* ------------------------------  PROTOTYPE   ------------------------------ */

	/* --------- checker_lst.c -------- */

void	ft_free_check_lst(t_check **top);
int		ft_check_lst_add_back(char *inst, t_check **top, t_check **last);

	/* --------- checker_utils.c -------- */

void	ft_get_instruction(t_check **inst, t_check **last);
int		ft_check_instruction(t_check *check);
int		ft_list_is_sorted(t_stack *a);
void	ft_apply_instruction(t_stack *a, t_stack *b, char	*inst);

#endif
