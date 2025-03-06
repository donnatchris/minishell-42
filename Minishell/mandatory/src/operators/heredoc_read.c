#include "../../include/minishell.h"

// Function to print error message in heredoc
static void heredoc_err(int n_line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 1);
	ft_putchar_fd((char)(n_line + 48), 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(delimiter, 1);
	ft_putstr_fd("')\n", 1);
}

// Function to end redir_heredoc_read
static void	end_redir_heredoc_read(char *line, int pipefd[])
{
	if (line)
		free(line);
	close(pipefd[1]);
	exit(0);
}

// Function to print the line to the fd
static void	print_heredoc_line(char *line, int fd, char **envp, int exit_status)
{
	char	*temp;

	temp = replace_each_dollar(line, envp, exit_status);
	ft_putstr_fd(temp, fd);
	free(temp);
	ft_putstr_fd("\n", fd);
}

// Function to read lines on the child process until delimiter is found
void    redir_heredoc_read(int pipefd[2], char **delimiters, char **envp, int exit_status)
{
	int     n_line;
	size_t	j;
	size_t	delimiter_size;
	char    *line;

	line = NULL;
	n_line = 0;
	j = 0;
	delimiter_size = count_env_size(delimiters);
	close(pipefd[0]);
	while (++n_line)
	{
		line = readline(CYAN "> " RESET);
		if (!line)
			heredoc_err(n_line, delimiters[j]);
		if (!ft_strncmp(line, delimiters[j], ft_strlen(delimiters[j])) && ft_strlen(line) == ft_strlen(delimiters[j]))
		{
			if (++j == delimiter_size)
				break ;
		}
		else if (j == delimiter_size - 1)//test
			print_heredoc_line(line, pipefd[1], envp, exit_status);
		free(line);
	}
	end_redir_heredoc_read(line, pipefd);
}