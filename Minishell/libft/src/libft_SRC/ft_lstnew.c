/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_lstnew.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: nifromon <marvin@42.fr>+#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2024/11/11 12:39:49 by nifromon  #+##+# */
/*   Updated: 2024/11/12 14:13:52 by nifromon ###   ########.fr   */
/**/
/* ************************************************************************** */

//START
#include "../../headers/libft_H/libft.h"

t_libft	*ft_lstnew(void *content)
{
	t_libft	*new_node;

	new_node = (t_libft *)malloc(sizeof(t_libft));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

//END
