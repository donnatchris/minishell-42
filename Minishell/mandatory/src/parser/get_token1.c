/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:12:12 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 04:16:51 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to get the next parenthesis from the input string
// Returns the type of the token
static int	get_parenthesis(char **s, char *es)
{
	int		depth;
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	if (**s == ')')
		return (ft_putstr_fd(str, 2), ft_putstr_fd("`)'\n", 2), TOKEN_ERROR);
	(*s)++;
	depth = 0;
	while (1)
	{
		if (*s == es)
			return (ft_putstr_fd(str, 2), ft_putstr_fd("`('\n", 2),
				TOKEN_ERROR);
		else if (**s == '(')
			depth++;
		else if (**s == ')')
		{
			if (depth == 0)
				break ;
			depth--;
		}
		(*s)++;
	}
	(*s)++;
	return (TOKEN_PARENTHESIS);
}

// Function to get the next angle bracket from the input string
// Returns the type of the token
static int	get_angle_bracket(char **s)
{
	int	ret;

	if (**s == '<')
	{
		ret = TOKEN_REDIR_IN;
		if (*(*s + 1) == '<')
		{
			ret = TOKEN_HEREDOC;
			(*s)++;
		}
	}
	else
	{
		ret = TOKEN_REDIR_OUT;
		if (*(*s + 1) == '>')
		{
			ret = TOKEN_APPEND;
			(*s)++;
		}
	}
	(*s)++;
	return (ret);
}

// Function to get the next symbol from the input string
// Returns the type of the token
static int	get_symbol(char **s, char *es)
{
	int	ret;

	ret = 0;
	if (**s == '>' || **s == '<')
		ret = get_angle_bracket(s);
	else if (**s == '(' || **s == ')')
		ret = get_parenthesis(s, es);
	else if (**s == ';')
		ret = get_semi_colon(s);
	else if (**s == '|')
		ret = get_vertical_bar(s);
	else if (**s == '&')
		ret = get_amperstand(s, es);
	else if (**s == '"')
		ret = double_quote(s, es);
	else if (**s == '\'')
		ret = get_single_quote(s, es);
	return (ret);
}

// Function to get the next word from the input string
// Returns the type of the token
static int	get_word(char **s, char *es)
{
	int	ret;

	ret = TOKEN_WORD;
	while (*s != es && !ft_strchr(WHITESPACES, **s) && !ft_strchr(SYMBOLS, **s))
		(*s)++;
	return (ret);
}

// Function to get the next token from the input string
// Returns the type of the token
int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACES, *s))
		s++;
	if (q)
		*q = s;
	if (s >= es)
		ret = TOKEN_EOF;
	else if (ft_strchr(SYMBOLS, *s))
		ret = get_symbol(&s, es);
	else
		ret = get_word(&s, es);
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(WHITESPACES, *s))
		s++;
	*ps = s;
	return (ret);
}
