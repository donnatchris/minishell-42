/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstmap.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 13:09:21 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:49:46 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

t_libft	*ft_lstmap(t_libft *lst, void *(*f)(void *), void (*del)(void *))
{
	t_libft	*new_lst;
	t_libft	*new_node;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		tmp = f(lst->content);
		if (!tmp)
			return (ft_lstclear(&new_lst, del), NULL);
		new_node = ft_lstnew(tmp);
		if (!new_node)
			return (ft_lstclear(&new_lst, del), del(tmp), NULL);
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

//END
