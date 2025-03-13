/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/13 15:35:25 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// // Function to find the next heredoc
// // Returns the node found or NULL if nothing is found
// static t_dclst	*next_heredoc(t_dclst *node)
// {
// 	t_token	*token;

// 	token = (t_token *) node->data;
// 	while (1)
// 	{
// 		node = node->next;
// 		token = (t_token *) node->data;
// 		if (token->type == TOKEN_HEREDOC)
// 			return (node);
// 		if (!is_text(node))
// 			break ;
// 	}
// 	return (NULL);
// }

// // Function to count the number of delimiters
// // Returns the number found
// static size_t	count_delimiters(t_dclst *node)
// {
// 	size_t	size;

// 	size = 1;
// 	while (1)
// 	{
// 		node = next_heredoc(node);
// 		if (!node)
// 			break ;
// 		size++;
// 	}
// 	return (size);
// }

// // Function to find the delimiters and create an array
// // Returns the next heredoc node, NULL if there is no more heredoc
// static char	**find_delimiters(t_dclst *node)
// {
// 	char	**delimiters;
// 	size_t	size;
// 	size_t	i;

// 	size = count_delimiters(node);
// 	delimiters = (char **) malloc(sizeof(char *) * (size + 1));
// 	if (!delimiters)
// 		return (ft_perror("find_delimiters", "malloc failed"), NULL);
// 	delimiters[0] = ft_strdup(((t_token *) node->next->data)->start);
// 	i = 1;
// 	while (i < size)
// 	{
// 		node = next_heredoc(node);
// 		delimiters[i] = ft_strdup(((t_token *) node->next->data)->start);
// 		i++;
// 	}
// 	delimiters[i] = NULL;
// 	return (delimiters);
// }

// // Function to handle multiple heredoc redirections '<<'
// // return 0 on success, return -1 on failure
// int	redir_heredoc(t_dclst *node, t_general *gen)
// {
// 	pid_t	pid;
// 	int		pipefd[2];
// 	char	**delimiters;

// 	if (!node || !gen)
// 		return (shell_err_msg("redir_heredoc", "invalid arguments"));
// 	if (pipe(pipefd) == -1)
// 		return (ft_perror("redir_heredoc", "pipe failed"));
// 	pid = fork();
// 	if (pid == -1)
// 		return (ft_perror("redir_heredoc", "fork failed"));
// 	delimiters = find_delimiters(node);
// 	if (pid == 0)
// 	{
// 		heredoc_signals();
// 		if (!delimiters)
// 			exit(-1);
// 		redir_heredoc_read(pipefd, delimiters, gen);
// 	}
// 	ignore_signals();
// 	delete_str_tab(delimiters);
// 	waitpid(pid, NULL, 0);
// 	init_signals();
// 	close(pipefd[1]);
// 	if (dup2(pipefd[0], STDIN_FILENO) == -1)
// 		return (close(pipefd[0]), ft_perror("redir_heredoc", "dup2 failed"));
// 	return (close(pipefd[0]), 0);
// }




// Function to redirect input from TEMP_FILE
// Returns 0 or -1 if it fails
int redir_heredoc()
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

// Function to print the line to the fd
static void	print_heredoc_line(int fd, char *line, t_general *gen)
{
	char	*temp;

	temp = replace_each_dollar(line, gen->envp, gen->exit_status);
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
static char	*find_delimiter(t_dclst *node, t_general *gen)
{
	t_token *tok;
	
	(void)gen;
	tok = (t_token *) node->next->data;
	return (tok->start);
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
			ft_printf("minishell: warning : here-document at line %d delimited by end-of-file (wanted `%s')\n", n_line, delimiter);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(line)) && ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		print_heredoc_line(fd, line, gen);
		free(line);
	}
	return (close(fd), 0);
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
