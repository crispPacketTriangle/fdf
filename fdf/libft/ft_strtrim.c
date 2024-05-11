/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:42:11 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:26:29 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, const char *set);
static int	count_f(const char *s1, const char *set);
static int	count_b(const char *s1, const char *set, int len);

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		len;
	int		size;
	char	*ptr;

	len = ft_strlen(s1);
	start = count_f(s1, set);
	size = len - (count_f(s1, set)) - (count_b(s1, set, len));
	if (size < 1)
		size = 0;
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], size + 1);
	return (ptr);
}

static int	is_in(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_f(const char *s1, const char *set)
{
	int	start;

	start = 0;
	while (is_in(s1[start], set))
	{
		start++;
	}
	return (start);
}

static int	count_b(const char *s1, const char *set, int len)
{
	int	i;

	i = 0;
	len -= 1;
	while (is_in(s1[len], set))
	{
		len--;
		i++;
	}
	return (i);
}

