/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 21:21:44 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to redirect input from TEMP_FILE
// Returns 0 or -1 if it fails
int redir_heredoc(void)
{
	int fd;

	fd = open(TEMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ft_perror("redir_heredoc", "open failed"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ft_perror("redir_heredoc", "dup2 failed"));
	close(fd);
	return (0);
}

static void	warning_msg(char *delimiter, int n_line)
{
	ft_putstr_fd("minishell: warning : here-document at line ", 2);
	ft_putnbr_fd(n_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

// Function to print the line written in heredoc to the fd
static void	print_heredoc_line(int fd, char *line, t_general *gen)
{
	char	*temp;

	temp = replace_each_dollar(line, gen);
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
// RETURNS MUST BE FREED AFTER USE
static char	*find_delimiter(t_dclst *node, t_general *gen)
{
	t_dclst	*current;
	t_token *tok;
	char	*delimiter;
	char	*temp;

	(void)gen;
	current = node->next;
	tok = (t_token *) current->data;
	delimiter = ft_strdup(tok->start);
	while (!tok->space && is_text(current->next))
	{
		temp = delimiter;
		delimiter = ft_strjoin(temp, ((t_token *) current->next->data)->start);
		free(temp);
		current = current->next;
		tok = (t_token *) current->data;
	}
	return (delimiter);
}

// Fonction pour créer un fichier temporaire contenant l'entrée du heredoc
static int create_heredoc_file(char *delimiter, t_general *gen)
{
	int			fd;
	char		*line;
	static int	n_line = 0;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_perror("create_heredoc", "open failed"));
	while (1)
	{
		n_line++;
		line = readline(CYAN "> " RESET);
		if (!line)
		{
			warning_msg(delimiter, n_line);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(line)) && ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		print_heredoc_line(fd, line, gen);
		if (line)
			free(line);
	}
	return (free(delimiter), close(fd), 0);
}

// Function to create the TEMP_FILE for heredoc
// Returns 0 or -1 if it fails
int create_heredoc(t_dclst *node, t_general *gen)
{
	t_dclst	*current;
	char	*delimiter;

	current = get_next_heredoc(node);
	while (1)
	{
		if (!current)
			break ;
		delimiter = find_delimiter(current, gen);
		if (create_heredoc_file(delimiter, gen))
			return (-1);
		current = get_next_heredoc(current->next);
	}
	return (0);
}
