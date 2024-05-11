/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:40:49 by lworden           #+#    #+#             */
/*   Updated: 2024/02/05 21:24:14 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*nxtln;
	static char	*ln[4069];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ln[fd] = fetch(fd, ln);
	if (!ln[fd])
		return (NULL);
	nxtln = set(ln, fd);
	ln[fd] = set_rem(ln, fd);
	return (nxtln);
}

char	*fetch(int fd, char **ln)
{
	char	*buff;
	int		rd;

	rd = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if ((read(fd, buff, 0)) < 0)
	{
		free(ln[fd]);
		return (freeb(buff));
	}
	while (isin(ln[fd]) < 0 && rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
			return (freeb(buff));
		buff[rd] = '\0';
		ln[fd] = gnl_strjoin(buff, ln, fd);
	}
	freeb(buff);
	return (ln[fd]);
}

char	*freeb(char *buff)
{
	free(buff);
	buff = NULL;
	return (NULL);
}

int	gnl_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	isin(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

