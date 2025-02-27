#include "../../include/minishell.h"

// Function to read lines on the child process until delimiter is found
// return nothing
void    redir_heredoc_child(int pipefd[2], char *delimiter)
{
    char *line;

    line = NULL;
    close(pipefd[0]); // Ferme la lecture
    while (1)
    {
        line = readline(CYAN "> " RESET);
        if (!line || strcmp(line, delimiter) == 0)
            break;
        ft_putstr_fd(line, pipefd[1]);
        ft_putstr_fd("\n", pipefd[1]);
        free(line);
    }
    free(line);
    close(pipefd[1]);
    exit(0);
}

// Function to handle the redirection '<<'
// return exec_tree on success, return -1 on failure
int redir_heredoc(t_tree *tree, char ***envp, t_general *gen)
{
    t_token *token;
    pid_t   pid;
    char    *delimiter;
    int     pipefd[2];
    int     stdin_backup;

    if (!tree || !envp || !gen)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    token = (t_token *)tree->list_node->next->data;
    if (!token || token->priority != 6 || !token->start)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    delimiter = token->start;
    if (pipe(pipefd) == -1)
        return (ft_perror("redir_heredoc", "pipe failed"));
    pid = fork();
    if (pid == -1)
        return (ft_perror("redir_heredoc", "fork failed"));
    if (pid == 0)
        redir_heredoc_child(pipefd, delimiter);
    waitpid(pid, NULL, 0);
    close(pipefd[1]); // ferme l'ecriture
    stdin_backup = dup(STDIN_FILENO);
    if (stdin_backup == -1)
        return (close(pipefd[0]), ft_perror("redir_heredoc", "dup failed"));
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        return (close(pipefd[0]), close(stdin_backup), ft_perror("redir_heredoc", "dup2 failed"));
    close(pipefd[0]);
    return (end_redir_in(tree, envp, gen, stdin_backup));
}
