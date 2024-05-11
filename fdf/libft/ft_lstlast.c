/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:11:06 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:08:50 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr_n;
	t_list	*ptr_c;

	if (lst == NULL)
		return (NULL);
	ptr_n = lst;
	ptr_c = ptr_n;
	while (ptr_n != NULL)
	{
		ptr_c = ptr_n;
		ptr_n = ptr_n->next;
	}
	return (ptr_c);
}

