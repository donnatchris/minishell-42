/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 23:04:33 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the next heredoc
// Returns the node found or NULL if nothing is found
static t_dclst	*next_heredoc(t_dclst *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	while (1)
	{
		node = node->next;
		token = (t_token *) node->data;
		if (token->type == TOKEN_HEREDOC)
			return (node);
		if (!is_text(node))
			break ;
	}
	return (NULL);
}

// Function to count the number of delimiters
// Returns the number found
static size_t	count_delimiters(t_dclst *node)
{
	size_t	size;

	size = 1;
	while (1)
	{
		node = next_heredoc(node);
		if (!node)
			break ;
		size++;
	}
	return (size);
}

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
static char	**find_delimiters(t_dclst *node)
{
	char	**delimiters;
	size_t	size;
	size_t	i;

	size = count_delimiters(node);
	delimiters = (char **) malloc(sizeof(char *) * (size + 1));
	if (!delimiters)
		return (ft_perror("find_delimiters", "malloc failed"), NULL);
	delimiters[0] = ft_strdup(((t_token *) node->next->data)->start);
	i = 1;
	while (i < size)
	{
		node = next_heredoc(node);
		delimiters[i] = ft_strdup(((t_token *) node->next->data)->start);
		i++;
	}
	delimiters[i] = NULL;
	return (delimiters);
}

// Function to handle multiple heredoc redirections '<<'
// return 0 on success, return -1 on failure
int	redir_heredoc(t_dclst *node, t_general *gen)
{
	pid_t	pid;
	int		pipefd[2];
	char	**delimiters;

	if (!node || !gen)
		return (shell_err_msg("redir_heredoc", "invalid arguments"));
	if (pipe(pipefd) == -1)
		return (ft_perror("redir_heredoc", "pipe failed"));
	pid = fork();
	if (pid == -1)
		return (ft_perror("redir_heredoc", "fork failed"));
	delimiters = find_delimiters(node);
	if (pid == 0)
	{
		heredoc_signals();
		if (!delimiters)
			exit(-1);
		redir_heredoc_read(pipefd, delimiters, gen);
	}
	ignore_signals();
	delete_str_tab(delimiters);
	waitpid(pid, NULL, 0);
	init_signals();
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (close(pipefd[0]), ft_perror("redir_heredoc", "dup2 failed"));
	return (close(pipefd[0]), 0);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// #define TMP_FILE "/tmp/minishell_heredoc.tmp"

// // Fonction pour créer un fichier temporaire contenant l'entrée du heredoc
// int create_heredoc(const char *delimiter) {
//     int fd;
//     char *line;

//     // Ouvrir le fichier temporaire en écriture
//     fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1) {
//         perror("open");
//         return -1;
//     }

//     // Lire l'entrée utilisateur jusqu'à ce que le délimiteur soit rencontré
//     while (1) {
//         line = readline("heredoc> ");
//         if (!line) {
//             // Ctrl+D détecté
//             printf("warning: end-of-file detected (delimiter '%s' not found)\n", delimiter);
//             break;
//         }
//         if (strcmp(line, delimiter) == 0) {
//             free(line);
//             break;
//         }
//         dprintf(fd, "%s\n", line); // Écrire la ligne dans le fichier temporaire
//         free(line);
//     }

//     close(fd);
//     return 0;
// }

// // Fonction pour rediriger l'entrée standard vers le fichier temporaire
// int redirect_heredoc() {
//     int fd;

//     // Ouvrir le fichier temporaire en lecture
//     fd = open(TMP_FILE, O_RDONLY);
//     if (fd == -1) {
//         perror("open");
//         return -1;
//     }

//     // Rediriger STDIN_FILENO vers le fichier temporaire
//     if (dup2(fd, STDIN_FILENO) == -1) {
//         perror("dup2");
//         close(fd);
//         return -1;
//     }

//     close(fd);
//     return 0;
// }

// // Fonction pour nettoyer le fichier temporaire
// void cleanup_heredoc() {
//     unlink(TMP_FILE); // Supprimer le fichier temporaire
// }

// // Exemple d'utilisation dans une commande
// int main() {
//     const char *delimiter = "EOF";

//     // Créer le heredoc
//     if (create_heredoc(delimiter) {
//         fprintf(stderr, "Erreur lors de la création du heredoc.\n");
//         return 1;
//     }

//     // Rediriger l'entrée standard vers le heredoc
//     if (redirect_heredoc()) {
//         fprintf(stderr, "Erreur lors de la redirection du heredoc.\n");
//         cleanup_heredoc();
//         return 1;
//     }

//     // Exécuter une commande (par exemple, `cat`)
//     execlp("cat", "cat", NULL);

//     // Nettoyer le fichier temporaire
//     cleanup_heredoc();

//     return 0;
// }