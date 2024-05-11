/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:20:52 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:19:04 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_c;

	c_c = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c_c)
			return ((char *)&s[i]);
		i++;
	}
	if (c_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

