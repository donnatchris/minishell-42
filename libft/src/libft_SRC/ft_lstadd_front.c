/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstadd_front.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 12:39:18 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:10:54 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

void	ft_lstadd_front(t_libft **lst, t_libft *new)
{
	new->next = *lst;
	*lst = new;
}

//END
