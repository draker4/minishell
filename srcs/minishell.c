/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 18:22:08 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_bracket(t_bracket *bracket, int what)
{
	t_bracket	*current;
	int			i;

	current = bracket;
	while (current)
	{
		if (current->child)
		{
			printf("current = %s has child\n", current->str);
			print_bracket(current->child, 1);
			//ft_child
		}
		
		if (current->pipe)
		{
			printf("current = %s has pipe\n", current->str);
			// ft_exec_pipe
			print_bracket(current->pipe, 2);
		}
		// else
		// 	exec_cmd
		i = 0;
		while (current->words[i])
			printf("current = %s et enum = %d et words = %s\n", current->str, current->type, current->words[i++]);
		if (what == 0)
			printf("racine\n");
		else if (what == 1)
			printf("child\n");
		else if (what == 2)
			printf("pipe\n");
		printf("current = %s et enum = %d\n", current->str, current->type);
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
	print_bracket(minishell->bracket, 0);
	// printf("debut = %s\n", minishell->bracket->str);
	// printf("ici child next = %s\n", minishell->bracket->child->next->str);
	}
	free(line);
	bracket_clear_data(&minishell->bracket);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	// int			boucle = 5;

	(void) argv;
	if (argc != 1)
	{
		write(2, "Please don't enter any argument!\n", 33);
		return (0);
	}
	if (!init_minishell(&minishell, envp))
		return (1);
	while (1)
		read_line(&minishell);
	free_split(minishell.path);
	return (0);
}
