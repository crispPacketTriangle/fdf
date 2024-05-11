/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:43:42 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:04:55 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	long long	mult;
	void		*ptr;
	long long	n_n;
	long long	s_s; 

	s_s = (long long)size;
	n_n = (long long)nmemb;
	if (n_n < 0 && s_s < 0)
		return (NULL);
	mult = n_n * s_s;
	if (mult > 2147483647 || mult < 0)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

