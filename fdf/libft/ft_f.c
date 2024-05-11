/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:16:21 by lworden           #+#    #+#             */
/*   Updated: 2024/01/26 19:56:35 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	u_f(va_list *ap)
{
	int					count;
	unsigned int		a;

	count = 0;
	a = va_arg(*ap, unsigned int);
	count = ubase(a, "0123456789", 10);
	return (count);
}

int	c_f(va_list *ap)
{
	char	*a;

	a = va_arg(*ap, char *);
	write(1, &a, 1);
	return (1);
}

int	s_f(va_list *ap)
{
	int		count;
	char	*a;

	a = va_arg(*ap, char *);
	count = 0;
	if (!a)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else 
	{
		while (*a)
		{
			write(1, a++, 1);
			count++;
		}
	}
	return (count);
}

int	b_f(va_list *ap)
{
	int			count;
	long long	a;

	count = 0;
	a = (long long)va_arg(*ap, int);
	if (a < 0)
	{
		write(1, "-", 1);
		a *= -1;
		count = 1;
	}
	count += base(a, "0123456789", 10);
	return (count);
}
