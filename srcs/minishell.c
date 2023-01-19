/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/19 13:33:08 by bperriol         ###   ########lyon.fr   */
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
		printf("current = %s\n", current->str);
		i = 0;
		while (current->words[i])
			printf("detail current = %s et enum = %d et words = %s\n", current->str, current->type, current->words[i++]);
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
	t_data	data;
	// int			boucle = 5;

	(void) argv;
	if (argc != 1)
		return (ft_putstr_color(COLOR_RED, ERROR_ARG, 2), 1);
	if (!init_data(&data, envp))
		return (1);
	while (1)
		read_line(&data);
	free_split(data.path);
	return (0);
}
