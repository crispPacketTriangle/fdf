/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:08:24 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:07:19 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*str_conv(int sign, long long n_n, char *ptr);
static long long	neg(long long n);
static void			rev(char *tab, int size);
static char			*mem(int len);

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	char		*ptr;
	long long	n_n;

	sign = 0;
	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		sign = 1;
	n_n = (long long)n;
	n_n = neg(n_n);
	while (n_n > 0)
	{
		n_n = n_n / 10;
		len++;
	}
	ptr = mem(len + sign);
	if (!ptr)
		return (NULL);
	n_n = neg((long long)n);
	str_conv(sign, n_n, ptr);
	rev(ptr, len + sign);
	return (ptr);
}

static char	*str_conv(int sign, long long n_n, char *ptr)
{
	long long	unit;
	int			i;

	if (n_n == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	i = 0;
	while (n_n > 0)
	{
		unit = n_n % 10;
		n_n = n_n / 10;
		ptr[i] = '0' + unit;
		i++;
	}
	if (sign == 1)
	{
		ptr[i] = '-';
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static long long	neg(long long n)
{
	if (n < 0)
	{
		n *= -1;
	}
	return (n);
}

static void	rev(char *tab, int size)
{
	int	c;
	int	n;
	int	len;

	n = 0;
	len = size - 1;
	while ((len - n) - n > 0)
	{
		c = tab[len - n];
		tab[len - n] = tab[n];
		tab[n] = c;
		n++;
	}
}

static char	*mem(int len)
{
	char	*ptr;

	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	return (ptr);
}

