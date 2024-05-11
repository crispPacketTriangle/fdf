/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:34:36 by lworden           #+#    #+#             */
/*   Updated: 2023/12/18 16:15:21 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_n(const char *str, char c);
static int	str_gen(const char *str, char c, char **arr, int n);
static void	free_all(char **arr);

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		n;
	int		t;

	n = str_n(str, c);
	arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[n] = NULL;
	t = str_gen(str, c, arr, n);
	if (!t)
	{
		free_all(arr);
		return (NULL);
	}
	return (arr);
}

static int	str_n(const char *str, char c)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			n++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (n);
}

static int	str_gen(const char *str, char c, char **arr, int n)
{
	int		i;
	int		str_i;
	int		j;

	i = 0;
	str_i = 0;
	while (n--)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			j = i;
			while (str[i] && str[i] != c)
				i++;
			arr[str_i] = ft_substr(str, j, i - j);
			if (!(arr[str_i]))
				return (0);
		}
		str_i++;
		while (str[i] == c)
			i++;
	}
	return (1);
}

static void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr)
	{
		free(arr[i++]);
	}
	free(arr);
}

