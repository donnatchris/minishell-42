/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:11:46 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 04:11:48 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to get the next single quote from the input string
// Returns the type of the token
int	get_single_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '\'')
		(*s)++;
	if (**s != '\'')
	{
		ft_putstr_fd("minishell: syntax error unclosed single quote\n", 2);
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
// Returns the type of the token
int	double_quote(char **s, char *es)
{
	int	ret;

	(*s)++;
	while (*s != es && **s != '"')
		(*s)++;
	if (**s != '"')
	{
		ft_putstr_fd("minishell: syntax error unclosed double quote\n", 2);
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
// Returns the type of the token
int	get_semi_colon(char **s)
{
	int	ret;

	ret = TOKEN_SEMICOLON;
	(*s)++;
	return (ret);
}

// Function to get the next amperstand from the input string
// Returns the type of the token
int	get_amperstand(char **s, char *es)
{
	int	ret;

	if (*(*s + 1) == '&')
	{
		ret = TOKEN_AND;
		(*s) += 2;
		return (ret);
	}
	ret = TOKEN_WORD;
	(*s)++;
	while (*s != es && !ft_strchr(WHITESPACES, **s) && !ft_strchr(SYMBOLS, **s))
		(*s)++;
	return (ret);
}

// Function to get te next vertical bar from the input string
// Returns the type of the token
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
