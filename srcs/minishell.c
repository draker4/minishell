/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/16 14:51:38 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_bracket(t_bracket *bracket)
{
	t_bracket	*current;
	int			i;

	current = bracket;
	while (current)
	{
		if (current->child)
			print_bracket(current->child);
		i = 0;
		while (current->words[i])
			printf("current = %s et enum = %d et words = %s\n", current->str, current->type, current->words[i++]);
		current = current->next;
	}
}

static void	read_line(t_minishell *minishell)
{
	char	*line;

	line = readline("minishell > ");
	if (check_line(line))
	{
		parse(line, &minishell->bracket, minishell->envp);
	// exec_brackets(minishell);
	print_bracket(minishell->bracket);
	// printf("debut = %s\n", minishell->bracket->str);
	// printf("ici child next = %s\n", minishell->bracket->child->next->str);
	}
	free(line);
	bracket_clear_data(&minishell->bracket);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			boucle = 5;

	(void) argv;
	if (argc != 1)
	{
		write(2, "Please don't enter any argument!\n", 33);
		return (0);
	}
	if (!init_minishell(&minishell, envp))
		return (1);
	while (boucle--)
		read_line(&minishell);
	free_split(minishell.path);
	return (0);
}
