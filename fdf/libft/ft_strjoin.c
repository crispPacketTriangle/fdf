/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:40:20 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:20:32 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *ptr, const char *s1, const char *s2);

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = 1;
	while (s1[i])
	{
		i++;
		size++;
	}
	i = 0;
	while (s2[i])
	{
		i++;
		size++;
	}
	ptr = (char *)malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	return (join(ptr, s1, s2)); 
}

static char	*join(char *ptr, const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[j] = s2[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

