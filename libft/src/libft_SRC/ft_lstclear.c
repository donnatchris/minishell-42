/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstclear.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 13:02:10 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:11:14 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

void	ft_lstclear(t_libft **lst, void (*del)(void *))
{
	t_libft	*tmp_lst;

	while (*lst != NULL)
	{
		tmp_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp_lst;
	}
	free(*lst);
	*lst = NULL;
}

//END
