/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:40:20 by lworden           #+#    #+#             */
/*   Updated: 2024/02/05 21:24:16 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set(char **ln, int fd)
{
	int		i;
	char	*nxtln;

	if (!ln[fd][0])
		return (NULL);
	i = 0;
	while (ln[fd][i] && ln[fd][i] != '\n')
		i++;
	nxtln = malloc((i + 2) * sizeof(char));
	if (!nxtln)
		return (NULL);
	i = 0;
	while (ln[fd][i] && ln[fd][i] != '\n')
	{
		nxtln[i] = ln[fd][i];
		i++;
	}
	if (ln[fd][i] == '\n')
	{
		nxtln[i] = ln[fd][i];
		i++;
	}
	nxtln[i] = '\0';
	return (nxtln);
}

char	*set_rem(char **ln, int fd)
{
	char	*cpyln;
	char	*rem;
	char	*remrtrn;
	int		i;

	if (!ln[fd][0])
		return (freel(ln, fd));
	i = 0;
	cpyln = ln[fd];
	while (*cpyln && *cpyln != '\n')
		cpyln++;
	if (*cpyln == '\n')
		cpyln++;
	while (cpyln[i])
		i++;
	rem = malloc((i + 2) * sizeof(char));
	if (!rem)
		return (NULL);
	remrtrn = rem;
	while (*cpyln)
		*rem++ = *cpyln++;
	*rem = '\0';
	free(ln[fd]);
	return (remrtrn);
}

char	*gnl_strjoin(char *buff, char **ln, int fd)
{
	int		len;
	int		j;
	char	*join;

	ln[fd] = set_line(ln, fd);
	join = malloc((gnl_strlen(ln[fd]) + gnl_strlen(buff) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	len = 0;
	while (ln[fd][len])
	{
		join[len] = ln[fd][len];
		len++;
	}
	j = len;
	len = 0;
	while (buff[len])
	{
		join[j] = buff[len];
		len++;
		j++;
	}
	join[j] = '\0';
	free(ln[fd]);
	return (join);
}

char	*set_line(char	**ln, int fd)
{
	if (!ln[fd])
	{
		ln[fd] = malloc(sizeof(char));
		ln[fd][0] = '\0';
	}
	return (ln[fd]);
}

char	*freel(char **ln, int fd)
{
	free(ln[fd]);
	return (NULL);
}

