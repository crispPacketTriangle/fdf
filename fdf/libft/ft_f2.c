/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:21:50 by lworden           #+#    #+#             */
/*   Updated: 2024/01/26 19:56:36 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	p_f(va_list *ap)
{
	int					count;
	unsigned long long	a;

	count = 0;
	a = va_arg(*ap, unsigned long long);
	if (!a)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count += 2;
	count += ubase(a, "0123456789abcdef", 16);
	return (count);
}

int	x_f(va_list *ap)
{
	int				count;
	unsigned int	a;

	count = 0;
	a = va_arg(*ap, unsigned int);
	count += base(a, "0123456789abcdef", 16);
	return (count);
}

int	xup_f(va_list *ap)
{
	int				count;
	unsigned int	a;

	a = va_arg(*ap, unsigned int);
	count = base(a, "0123456789ABCDEF", 16);
	return (count);
}
