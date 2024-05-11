/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:12:09 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:21:43 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(const char *big, const char *little, size_t i, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)big;
	i = 0;
	if (!(ft_strlen(little)))
		return (ptr);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			if (match(big, little, i, len))
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}

static int	match(const char *big, const char *little, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (little[j])
	{
		if (big[i] != little[j] || !(i < len))
			return (0);
		i++;
		j++;
	}
	return (1);
}

