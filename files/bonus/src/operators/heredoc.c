/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 13:06:24 by christophed      ###   ########.fr       */
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
static void	print_heredoc_line(int fd, char *line, t_general *gen, t_delim *delim)
{
	char	*temp;

	if (delim->is_litteral)
		temp = ft_strdup(line);
	else
		temp = replace_each_dollar(line, gen);
	if (!temp)
		return ;
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
// RETURNS MUST BE FREED AFTER USE
static t_delim	*find_delimiter(t_dclst *node)
{
	t_delim	*delimiter;
	t_dclst	*current;
	t_token *tok;
	char	*temp;

	delimiter = (t_delim *) malloc(sizeof(t_delim));
	if (!delimiter)
		return (shell_err_msg("find_delimiter", "malloc failed"), NULL);
	ft_memset(delimiter, 0, sizeof(t_delim));
	current = node->next;
	tok = (t_token *) current->data;
	delimiter->str = ft_strdup(tok->start);
	if (tok->type != TOKEN_WORD)
		delimiter->is_litteral = 1;
	if (!delimiter->str)
		return (shell_err_msg("find_delimiter", "ft_strdup failed"), NULL);
	while (!tok->space && is_text(current->next))
	{
		if (tok->type != TOKEN_WORD || ((t_token *) current->next->data)->type != TOKEN_WORD)
			delimiter->is_litteral = 1;
		temp = delimiter->str;
		delimiter->str = ft_strjoin(temp, ((t_token *) current->next->data)->start);
		free(temp);
		current = current->next;
		tok = (t_token *) current->data;
	}
	return (delimiter);
}

// Fonction pour créer un fichier temporaire contenant l'entrée du heredoc
static int create_heredoc_file(t_delim *delim, t_general *gen)
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
			warning_msg(delim->str, n_line);
			break ;
		}
		if (!ft_strncmp(line, delim->str, ft_strlen(line)) && ft_strlen(line) == ft_strlen(delim->str))
		{
			free(line);
			break ;
		}
		print_heredoc_line(fd, line, gen, delim);
		if (line)
			free(line);
	}
	return (delete_delim(delim), close(fd), 0);
}

// Function to create the TEMP_FILE for heredoc
// Returns 0 or -1 if it fails
int create_heredoc(t_dclst *node, t_general *gen)
{
	t_dclst	*current;
	t_delim	*delimiter;

	current = get_next_heredoc(node);
	while (1)
	{
		if (!current)
			break ;
		delimiter = find_delimiter(current);
		if (!delimiter)
			return (-1);
		if (create_heredoc_file(delimiter, gen))
			return (-1);
		current = get_next_heredoc(current->next);
	}
	return (0);
}
