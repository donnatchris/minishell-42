/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:37:36 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 09:06:50 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to print error message in heredoc
static void	heredoc_err(int n_line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 1);
	ft_putchar_fd((char)(n_line + 48), 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}

// Function to end redir_heredoc_read
static void	end_redir_heredoc_read(int fd[], char ** limiters, t_general *gen)
{
	delete_str_tab(limiters);
	close(fd[1]);
	close(gen->stdin_backup);
	close(gen->stdout_backup);
	delete_general(gen);
	exit(0);
}

// Function to print the line to the fd
static void	print_heredoc_line(char *line, int fd, char **envp, int ex_stat)
{
	char	*temp;

	temp = replace_each_dollar(line, envp, ex_stat);
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Function to initialize heredoc read values
static void	init_heredoc_read_values(char **line, int *n_line, size_t *j)
{
	*line = NULL;
	*n_line = 0;
	*j = 0;
}

// Function to read lines on the child process until delimiter is found
void	redir_heredoc_read(int fd[2], char **limiters, char **envp, t_general *gen)
{
	int		n_line;
	size_t	j;
	size_t	limiter_size;
	char	*line;

	init_heredoc_read_values(&line, &n_line, &j);
	limiter_size = count_env_size(limiters);
	close(fd[0]);
	while (++n_line)
	{
		line = readline(CYAN "> " RESET);
		if (!line)
			heredoc_err(n_line, limiters[j++]);
		else if (line && limiters[j] && ft_strlen(line) == ft_strlen(limiters[j]) && !ft_strncmp(line, limiters[j], ft_strlen(limiters[j])))
			j++;
		else if (j == limiter_size - 1)
			print_heredoc_line(line, fd[1], envp, gen->exit_status);
		if (line)
			free(line);
		if (j == limiter_size)
			break ;
	}
	end_redir_heredoc_read(fd, limiters, gen);
}
