/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/17 15:09:35 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to redirect input from TEMP_FILE
// Returns 0 or -1 if it fails
int	redir_heredoc(void)
{
	int	fd;

	fd = open(TEMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ft_perror("redir_heredoc", "open failed"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ft_perror("redir_heredoc", "dup2 failed"));
	close(fd);
	return (0);
}

// Function to print the line written in heredoc to the fd
static void	print_heredoc_line(int fd, char *line, t_general *gen, t_delim *lim)
{
	char	*temp;

	if (lim->is_litteral)
		temp = ft_strdup(line);
	else
		temp = replace_each_dollar(line, gen);
	if (!temp)
		return ;
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Fonction pour créer un fichier temporaire contenant l'entrée du heredoc
static int	create_heredoc_file(t_delim *delim, t_general *gen)
{
	int			fd;
	char		*line;
	static int	n_line = 0;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_perror("create_heredoc", "open failed"));
	while (++n_line)
	{
		line = readline(CYAN "> " RESET);
		if (!line)
		{
			warning_msg(delim->str, n_line);
			break ;
		}
		if (!ft_strncmp(line, delim->str, ft_strlen(line))
			&& ft_strlen(line) == ft_strlen(delim->str))
		{
			free(line);
			break ;
		}
		print_heredoc_line(fd, line, gen, delim);
		free(line);
	}
	return (delete_delim(delim), close(fd), 0);
}

// Function to create the TEMP_FILE in a child process
// Returns 0 or -1 if it fails
void	heredoc_child_proc(t_dclst *node, t_general *gen)
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
		{
			delete_general(gen);
			exit(-1);
		}
		if (create_heredoc_file(delimiter, gen))
		{
			delete_general(gen);
			exit(-1);
		}
		current = get_next_heredoc(current->next);
	}
	delete_general(gen);
	exit(0);
}

// Function to create the TEMP_FILE for heredoc
// Returns 0 or -1 if it fails
int	create_heredoc(t_dclst *node, t_general *gen)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (ft_perror("create_heredoc", "fork failed"));
	if (pid == 0)
		heredoc_child_proc(node, gen);
	if (waitpid(pid, NULL, 0) == -1)
		return (ft_perror("create_heredoc", "waitpid failed"));
	if (WIFEXITED(pid) && WEXITSTATUS(pid) == -1)
		return (-1);
	return (0);
}
