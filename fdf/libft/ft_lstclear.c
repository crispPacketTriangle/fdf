/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:14:13 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:08:32 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*node;

	if (!(*lst))
		return ;
	ptr = (*lst)->next;
	node = *lst;
	while (node != NULL)
	{
		ptr = node->next;
		del((node)->content);
		free(node);
		node = ptr;
	}
	*lst = NULL;
}

