#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to get the next single quote from the input string
int	get_single_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '\'')
		(*s)++;
	if (**s != '\'')
	{
		ft_putstr_fd("syntax error unclosed single quote\n", 2);
		ret = TOKEN_ERROR;
	}
	else
	{
		ret = TOKEN_LITTERAL;
		(*s)++;
	}
	return (ret);
}

// Function to get the next double quote from the input string
int	double_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '"')
		(*s)++;
	if (**s != '"')
	{
		ft_putstr_fd("syntax error unclosed double quote\n", 2);
		ret = TOKEN_ERROR;
	}
	else
	{
		ret = TOKEN_STRING;
		(*s)++;
	}
	return (ret);
}

// Function to get the next semi-colon from the input string
int	get_semi_colon(char **s)
{
	int	ret;

	ret = TOKEN_SEMICOLON;
	(*s)++;
	return (ret);
}

// Function to get the next amperstand from the input string
int	get_amperstand(char **s)
{
	int	ret;

	ret = TOKEN_WORD;
	if (*(*s + 1) == '&')
	{
		ret = TOKEN_AND;
		(*s)++;
	}
	(*s)++;
	return (ret);
}

// Function to get te next vertical bar from the input string
int	get_vertical_bar(char **s)
{
	int	ret;

	ret = TOKEN_PIPE;
	if (*(*s + 1) == '|')
	{
		ret = TOKEN_OR;
		(*s)++;
	}
	(*s)++;
	return (ret);
}

// Function to get the next parenthesis from the input string
int	get_parenthesis(char **s, char *es)
{
	int	depth;

	if (**s == ')')
		return (ft_putstr_fd("syntax error near unexpected token `)'\n", 2), TOKEN_ERROR);
	(*s)++;
	depth = 0;
	while (1)
	{
		if (*s == es)
			return (ft_putstr_fd("syntax error unclosed bracket\n", 2), TOKEN_ERROR);
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
int	get_angle_bracket(char **s)
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
int	get_symbol(char **s, char *es)
{
	int	ret;

	if (**s == '>' || **s == '<')
		ret = get_angle_bracket(s);
	else if (**s == '(' || **s == ')')
		ret = get_parenthesis(s, es);
	else if (**s == ';')
		ret = get_semi_colon(s);
	else if (**s == '|')
		ret = get_vertical_bar(s);
	else if (**s == '&')
		ret = get_amperstand(s);
	else if (**s == '"')
		ret = double_quote(s, es);
	else if (**s == '\'')
		ret = get_single_quote(s, es);
	else
	{
		ret = 0;
		ft_printf("c est quoi cette merde\n");
		// a retirer avant de rendre
	}
	return (ret);
}
//test
// Function to get the next word from the input string
int	get_word(char **s, char *es)
{
	int	ret;

	ret = TOKEN_WORD;
	while (*s != es && !ft_strchr(WHITESPACES, **s) && !ft_strchr(SYMBOLS, **s))
		(*s)++;
	return (ret);
}

// Function to get the next token from the input string
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
