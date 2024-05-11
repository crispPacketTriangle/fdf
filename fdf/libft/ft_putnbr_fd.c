/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:20:55 by lworden           #+#    #+#             */
/*   Updated: 2023/12/15 16:16:27 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		max_chk(int nb, int fd);
static void		prnt(char *arr, int i, int fd);

void	ft_putnbr_fd(int nb, int fd)
{
	int		digit;
	int		i;
	char	arr[32]; 

	if (max_chk(nb, fd))
		return ;
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	i = 0;
	digit = -1;
	while (nb != 0)
	{
		digit = nb % 10;
		nb = (nb - digit) / 10;
		arr[i] = '0' + digit;
		i++;
	}
	prnt(arr, i, fd);
}

static	int	max_chk(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (nb == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

static void	prnt(char *arr, int i, int fd)
{
	i -= 1;
	while (i > -1)
	{
		write(fd, &arr[i], 1);
		i--;
	}
}

