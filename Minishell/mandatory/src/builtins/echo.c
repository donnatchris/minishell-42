#include "../../include/minishell.h"

void	echo_cmd(t_dclst *start, t_dclst *end, char **envp)
{
	int		newline;
	char	*str;
	t_token	*token;
	t_dclst	*current;

	if (!start)
		return ;
	newline = 0;
	current = skip_newline_flags(start, end, &newline, envp);
	while (1)
	{
		token = (t_token *)current->data;
		str = manage_dollar(token, envp);
		ft_putstr_fd(str, 1);
		free(str);
		if (current == end || !end)
			break ;
		ft_putchar_fd(' ', 1);
		current = current->next;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
}

t_dclst	*skip_newline_flags(t_dclst *start, t_dclst *end, int *newline, char **envp)
{
	t_token	*token;
	t_dclst	*current;

	if (start == end)
		return (start);
	current = start;
	while (1)
	{
		token = (t_token *)current->data;
		if (newline_flag(token, newline, envp) == 1 || current == end)
			break ;
		current = current->next;
	}
	return (current);
}

int	newline_flag(t_token *token, int *newline, char **envp)
{
	int	i;
	char	*str;

	i = 2;
	str = manage_dollar(token, envp);
	if (ft_strncmp(str, "-n", 2) != 0)
		return (free(str), 1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (free(str), 1);
		i++;
	}
	*newline = 1;
	return (free(str), 0);
}
