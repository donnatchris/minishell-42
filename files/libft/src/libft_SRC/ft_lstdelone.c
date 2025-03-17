/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstdelone.c :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 12:58:15 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:13:06 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

void	ft_lstdelone(t_libft *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

//END
