/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:04:12 by lworden           #+#    #+#             */
/*   Updated: 2024/01/26 19:56:40 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base(long long x, char *base, int b)
{
	int	n;

	n = 0;
	n = rec(x, base, b, n);
	write(1, &base[x % b], 1);
	n++;
	return (n);
}

int	rec(long long x, char *base, int b, int n)
{
	if (x > 0)
	{
		x = x / b;
		n += rec(x, base, b, n);
		if (x > 0)
		{
			write(1, &base[x % b], 1);
			return (++n);
		}
	}
	return (n);
}

int	ubase(unsigned long long x, char *base, int b)
{
	int	n;

	n = 0;
	n = urec(x, base, b, n);
	write(1, &base[x % b], 1);
	n++;
	return (n);
}

int	urec(unsigned long long x, char *base, int b, int n)
{
	if (x > 0)
	{
		x = x / b;
		n += urec(x, base, b, n);
		if (x > 0)
		{
			write(1, &base[x % b], 1);
			return (++n);
		}
	}
	return (n);
}
