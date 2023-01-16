/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 16:25:06 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
/* ------------------------------  STRUCTURE  ------------------------------- */

	/*Structure des listes chainées.*/
typedef struct s_arg
{
	int				data;
	int				order;
	int				move_a;
	int				move_b;
	struct s_arg	*prev;
	struct s_arg	*next;
}					t_arg;

	/*Structure des stacks.*/
typedef struct s_stack
{
	int				size;
	int				min;
	int				max;
	int				move_a;
	int				move_b;
	int				move_total;
	t_arg			*top;
	t_arg			*last;
}					t_stack;

/* ------------------------------  PROTOTYPE   ------------------------------ */

	/* --------- ft_arg_list.c -------- */

int		ft_arg_size(t_arg *arg);
int		ft_free_arg(t_stack *stack);
t_arg	*ft_new_arg(int data);
int		ft_add_back(int data, t_stack *a);

	/* --------- ft_define_order.c -------- */

int		ft_define_move_to_top(t_stack *stack, int order);
void	ft_define_next_move(t_stack *a, t_stack *b);

	/* --------- ft_define_order.c -------- */

void	ft_push_bloc(t_stack *a, t_stack *b);
int		ft_define_order(t_stack *a);

	/* --------- ft_parse.c -------- */

void	ft_parse(int argc, char **argv, t_stack *a);

	/* --------- ft_push.c -------- */

void	ft_push_a(t_stack *a, t_stack *b, int print);
void	ft_push_b(t_stack *a, t_stack *b, int print);

	/* --------- ft_realise_move.c -------- */

void	ft_realise_move(t_stack *a, t_stack *b);
void	ft_final_sort(t_stack *a);

	/* --------- ft_reverse.c -------- */

void	ft_reverse_a(t_stack *a, int print);
void	ft_reverse_b(t_stack *b, int print);
void	ft_reverse_r(t_stack *a, t_stack *b, int print);

	/* --------- ft_rotate.c -------- */

void	ft_rotate_a(t_stack *a, int print);
void	ft_rotate_b(t_stack *b, int print);
void	ft_rotate_r(t_stack *a, t_stack *b, int print);

	/* --------- ft_sort_simple.c -------- */

void	ft_sort_three(t_stack *a);
void	ft_sort_five(t_stack *a, t_stack *b);

	/* --------- ft_swap.c -------- */

void	ft_swap_a(t_stack *a, int print);
void	ft_swap_b(t_stack *a, int print);
void	ft_swap_s(t_stack *a, t_stack *b, int print);

#endif
