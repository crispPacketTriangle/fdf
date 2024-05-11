/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:49:38 by lworden           #+#    #+#             */
/*   Updated: 2024/01/26 19:56:42 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			(*g_fc_arr[8])(va_list *ap) = {b_f, b_f, u_f, 
	c_f, s_f, p_f, x_f, xup_f};
const char	*g_types = "diucspxX";

int	ft_printf(const char *args, ...)
{
	int		i;
	va_list	v_ap;
	va_list	*ap;

	i = 0;
	ap = &v_ap;
	va_start(*ap, args);
	w_out(&i, args, ap);
	va_end(*ap);
	return (i);
}

void	w_out(int *i, const char *args, va_list *ap)
{
	int	f;

	while (*args)
	{
		if (*args == '%')
		{
			f = -1;
			f = pf_isin(*(args + 1), g_types);
			if (f != -1)
			{
				(*i) += call(f, ap);
				args += 2;
			}
			else
				args++;
		}
		if (*args && !(*args == '%' && f != -1))
		{
			write(1, args, 1);
			args++;
			(*i)++;
		}
	}
}

int	pf_isin(char c, const char *g_types)
{
	int	i;

	i = 0;
	while (g_types[i])
	{
		if (g_types[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	call(int f, va_list *ap)
{
	int	i;

	i = g_fc_arr[f](ap);
	return (i);
}

