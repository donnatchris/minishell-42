/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:21:47 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 15:04:57 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Global variable for handling signals
int	g_signals;

static void	starting_message(void)
{
	char	*msg;
	int		i;
	int		delay;

	delay = 10000;
	msg = BLUE "Welcome to minishell, a (not so) simple shell\
	- by chdonnat and nifromon" RESET;
	ft_printf("\033[2J");
	ft_printf("\033[H");
	i = -1;
	while (msg[++i])
	{
		ft_putchar_fd(msg[i], STDOUT_FILENO);
		usleep(delay);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

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

	starting_message();
	gen = NULL;
	gen = init_gen(gen, envp, av, ac);
	while (g_signals != EOF)
	{
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
		if (check_syntax(gen->head, gen, NO_PARENTHESIS))
			continue ;
		gen->tree = create_tree(*gen->head, (*gen->head)->prev->prev);
		exec_tree(gen->tree, gen);
	}
	ft_printf("exit\n");
	delete_before_close(gen);
	return (0);
}
