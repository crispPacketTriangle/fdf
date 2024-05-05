/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:32:50 by lworden           #+#    #+#             */
/*   Updated: 2024/05/05 20:47:08 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calc_axes(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = open(filename, O_RDONLY);
	r_vars.line = get_next_line(r_vars.fd);
	if (!(r_vars.line) || r_vars.fd < 0)
		return (-1);
	r_vars.p_line = ft_split(r_vars.line, ' ');
	r_vars.i = 0;
	while (r_vars.p_line[r_vars.i])
	{
		r_vars.i++;
		maps->xaxis++;
	}
	while (r_vars.line)
	{
		maps->yaxis++;
		free(r_vars.line);
		r_vars.line = get_next_line(r_vars.fd);
	}
	free_all(&r_vars, 1);
	return (0);
}

int	init_arrs(t_maps *maps)
{
	int	i;

	maps->map_vec = malloc(maps->yaxis * sizeof(t_vec *));
	if (!maps->map_vec)
		return (-1);
	i = 0;
	while (i < maps->yaxis)
	{
		maps->map_vec[i] = malloc(maps->xaxis * sizeof(t_vec));
		if (!maps->map_vec[i])
			return (-1);
		i++;
	}
	return (0);
}

int	init_zaxis(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = open(filename, O_RDONLY);
	if (r_vars.fd < 0)
		return (-1);
	r_vars.i = 0;
	while (r_vars.i < maps->yaxis)
	{
		r_vars.line = get_next_line(r_vars.fd);
		r_vars.p_line = ft_split(r_vars.line, ' ');
		r_vars.j = 0;
		while (r_vars.j < maps->xaxis)
		{
			maps->map_vec[r_vars.i][r_vars.j].z
				= ft_atoi(r_vars.p_line[r_vars.j]);
			r_vars.j++;
		}
		free_all(&r_vars, 0);
		r_vars.i++;
	}
	flush_gnl(&r_vars);
	close(r_vars.fd);
	return (0);
}

void	flush_gnl(t_read *r_vars)
{
	while (r_vars->line)
	{
		r_vars->line = get_next_line(r_vars->fd);
		free(r_vars->line);
	}
}
