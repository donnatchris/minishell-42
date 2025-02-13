/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   libft.h:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/04 13:56:31 by nifromon  #+##+# */
/*   Updated: 2024/11/11 13:24:59 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "libft_typedef.h"

// Mandatory fonctions
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// Bonus Fonctions
t_libft		*ft_lstnew(void *content);
void		ft_lstadd_front(t_libft **lst, t_libft *new);
int			ft_lstsize(t_libft *lst);
t_libft		*ft_lstlast(t_libft *lst);
void		ft_lstadd_back(t_libft **lst, t_libft *new);
void		ft_lstdelone(t_libft *lst, void (*del)(void *));
void		ft_lstclear(t_libft **lst, void (*del)(void *));
void		ft_lstiter(t_libft *lst, void (*f)(void *));
t_libft		*ft_lstmap(t_libft *lst, void *(*f)(void *), void (*del)(void *));

#endif

//END
