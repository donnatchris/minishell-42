#include "../../include/minishell.h"

// Function to print eof uncounter warning
void    redir_heredoc_eofmsg(int c, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 1);
	ft_putchar_fd(c, 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}
//test
// Function to read lines on the child process until delimiter is found
// return nothing
void    redir_heredoc_read(int pipefd[2], char *delimiter, char **envp, int exit_status)
{
    int     i;
    char    *line;
	char	*temp; // to test

    line = NULL;
    i = 0;
	init_heredoc_signals();
    close(pipefd[0]); // Ferme la lecture
    while (1)
    {
        i++;
        line = readline(CYAN "> " RESET);
        if (!line)
			redir_heredoc_eofmsg((i + 48), delimiter);
        if (ft_strncmp(line, delimiter, (int)ft_strlen(delimiter)) == 0
            && ft_strlen(delimiter) == ft_strlen(line))
            break;
		temp = replace_each_dollar(line, envp, exit_status);
        ft_putstr_fd(temp, pipefd[1]);
		free(temp);
        ft_putstr_fd("\n", pipefd[1]);
        free(line);
    }
    free(line);
    close(pipefd[1]); // ferme l'ecriture
    exit(0);
}

// Function to handle the redirection '<<'
// return exec_tree on success, return -1 on failure
int redir_heredoc(t_dclst *node, char ***envp, t_general *gen)
{
    t_token *token;
    pid_t   pid;
    int     pipefd[2];

    if (!node || !envp || !gen)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    token = (t_token *) node->next->data;
    if (!token || token->priority != 6 || !token->start)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    if (pipe(pipefd) == -1)
		return (ft_perror("redir_heredoc", "pipe failed"));
    pid = fork();
    if (pid == -1)
		return (ft_perror("redir_heredoc", "fork failed"));
	init_main_signals(0);
    if (pid == 0)
        redir_heredoc_read(pipefd, token->start, *envp, gen->exit_status);
    waitpid(pid, NULL, 0);
	init_main_signals(1);
    close(pipefd[1]); // ferme l'ecriture
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        return (close(pipefd[0]), ft_perror("redir_heredoc", "dup2 failed"));
    close(pipefd[0]); // ferme la lecture
    return (0);
}
