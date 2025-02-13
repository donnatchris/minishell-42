/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_split.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/06 14:34:47 by nifromon  #+##+# */
/*   Updated: 2024/11/07 10:06:13 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

/*#include <stdio.h>*/
//START
#include "../../headers/libft_H/libft.h"

static size_t	word_count(const char *s, char delimiter)
{
	size_t	i;
	size_t	in_word;
	size_t	count;

	i = 0;
	in_word = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == delimiter)
		{
			in_word = 0;
			i++;
		}
		else if (s[i] != delimiter)
		{
			if (in_word == 0)
			{
				in_word = 1;
				count++;
			}
			i++;
		}
	}
	return (count);
}

static char	*strndup_checkpoint(const char *s, size_t n, size_t checkpoint)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (s == NULL)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * n + 1);
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = s[i + checkpoint];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	free_split(char **split, size_t nallocated_words)
{
	size_t	i;

	i = 0;
	while (i < nallocated_words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	checkpoint;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	split = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (j < word_count(s, c))
	{
		while (s[i] == c)
			i++;
		checkpoint = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		split[j] = strndup_checkpoint(s, (i - checkpoint), checkpoint);
		if (split[j] == NULL)
			return (free_split(split, j), NULL);
		j++;
	}
	split[j] = NULL;
	return (split);
}

//END
/*int	main(void)
{
	size_t	i;
	char	**res;

	printf("\nTest de ft_split :\n\n");
	printf("Chaine s : 'bonjour a tous', separateur c : ' ', resultat :\n");
	res = ft_split("bonjour a tous", ' ');
	i = 0;
	while (res[i])
	{
		printf("'%s'", res[i]);
		i++;
	}
	printf("\n\nChaine s:' bonjour a tous ',separateur c:' ',resultat :\n");
	res = ft_split(" bonjour a tous ", ' ');
	i = 0;
	while (res[i])
	{
		printf("'%s'", res[i]);
		i++;
	}
	printf("\n\nChaine s : '   ', separateur c : ' ', resultat :\n");
	res = ft_split("   ", ' ');
	i = 0;
	while (res[i])
	{
		printf("'%s'", res[i]);
		i++;
	}
	printf("\n\nChaine s : ' d  ', separateur c : ' ', resultat :\n");
	res = ft_split(" d  ", ' ');
	i = 0;
	while (res[i])
	{
		printf("'%s'", res[i]);
		i++;
	}
	printf("\n\nChaine s : 'nosep', separateur c : ' ', resultat :\n");
	res = ft_split("nosep", ' ');
	i = 0;
	while (res[i])
	{
		printf("'%s'", res[i]);
		i++;
	}
	printf("\n\n");
	return (0);
}*/
