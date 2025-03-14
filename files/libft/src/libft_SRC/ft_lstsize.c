/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstsize.c   :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 12:37:45 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:12:49 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

int	ft_lstsize(t_libft *lst)
{
	int		i;
	t_libft	*tmp_lst;

	i = 0;
	tmp_lst = lst;
	while (tmp_lst != NULL)
	{
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (i);
}

//END
