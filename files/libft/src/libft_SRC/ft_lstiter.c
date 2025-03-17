/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstiter.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 13:06:04 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:11:36 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

void	ft_lstiter(t_libft *lst, void (*f)(void *))
{
	t_libft	*tmp_lst;

	tmp_lst = lst;
	while (tmp_lst != NULL)
	{
		f(tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
}

//END
