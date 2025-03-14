/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:21:47 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 15:26:05 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Global variable for handling signals
int	g_signals;

// Function to affect values of the general structure
static void	affect_gen_values(t_general *gen)
{
	gen->in_start = gen->input;
	gen->in_end = gen->input + ft_strlen(gen->input);
	gen->input_cpy = ft_strdup(gen->input);
	gen->head = tokenize(gen->input);
}

// Function main to launch the minishell
int	main(int ac, char **av, char **envp)
{
	t_general	*gen;

	gen = NULL;
	gen = init_gen(gen, envp, av, ac);
	while (g_signals != EOF)
	{
		g_signals = 0;
		init_signals();
		delete_cmd_line(gen);
		gen->input = readline(CYAN "MINISHELL > " RESET);
		if (!gen->input)
			break ;
		if (gen->input && gen->input[0] != '\n' && gen->input[0] != '\0')
			add_history(gen->input);
		if (!gen->input[0] || gen->input[0] == '\n')
			continue ;
		affect_gen_values(gen);
		if (check_syntax(gen->head, gen, NO_PARENTHESIS) == -1)
			continue ;
		gen->tree = create_tree(*gen->head, (*gen->head)->prev->prev);
		exec_tree(gen->tree, gen);
	}
	ft_printf("exit\n");
	delete_before_close(gen);
	return (0);
}
