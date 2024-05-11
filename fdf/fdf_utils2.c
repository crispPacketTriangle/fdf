/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:53:59 by lworden           #+#    #+#             */
/*   Updated: 2024/05/11 17:46:07 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vecs(t_vars *p_vars, void *mlx_ptr, void *win_ptr)
{
	int	i;
	int	j;

	i = 0;
	while (i < p_vars->m->yaxis)
	{
		j = 0;
		while (j < p_vars->m->xaxis)
		{
			draw_image(p_vars, p_vars->m->map_vec[i][j].x,
				p_vars->m->map_vec[i][j].y, p_vars->white);
			j++;
		}
		i++;
	}
}

void	draw_x_plane(t_vars *p_vars, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed.i = 0;
	while (ed.i < p_vars->m->yaxis)
	{
		ed.j = 0;
		while (ed.j < p_vars->m->xaxis - 1)
		{
			ed_setup(p_vars->m, &ed, 0);
			ed.g_o = gradient(ed.exx, ed.exx2, ed.yy, ed.xy2);
			ed.x = p_vars->m->map_vec[ed.i][ed.j].x;
			ed.y_o = p_vars->m->map_vec[ed.i][ed.j].y_o;
			while (ed.x < p_vars->m->map_vec[ed.i][ed.j + 1].x)
			{
				draw_image(p_vars, ed.x, ed.y_o, p_vars->dark_green);
				ed.x++;
				ed.y_o += ed.g_o;
			}
			ed.j++;
		}
		ed.i++;
	}
}

void	draw_y_plane(t_vars *p_vars, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed.i = 0;
	while (ed.i < p_vars->m->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < p_vars->m->xaxis)
		{
			ed_setup(p_vars->m, &ed, 1);
			ed.g_o = gradient(ed.yy, ed.yy2, ed.exx, ed.eyx2);
			ed.x = p_vars->m->map_vec[ed.i][ed.j].x;
			ed.y_o = p_vars->m->map_vec[ed.i][ed.j].y_o;
			while (ed.y_o < p_vars->m->map_vec[ed.i + 1][ed.j].y_o)
			{
				draw_image(p_vars, ed.x, ed.y_o, p_vars->dark_green);
				ed.x += ed.g_o;
				ed.y_o++;
			}
			ed.j++;
		}
		ed.i++;
	}
}

int	draw(t_vars *p_vars)
{
	calc_vect(p_vars->m, p_vars);
	fill(p_vars, p_vars->addr);
	if (0 < p_vars->toggle_plane)
	{
		draw_x_plane(p_vars, p_vars->mlx_ptr, p_vars->win_ptr);
		draw_y_plane(p_vars, p_vars->mlx_ptr, p_vars->win_ptr);
	}
	if (0 < p_vars->toggle_grid)
	{
		draw_x_edges(p_vars, p_vars->mlx_ptr, p_vars->win_ptr);
		draw_y_edges(p_vars, p_vars->mlx_ptr, p_vars->win_ptr);
	}
	mlx_put_image_to_window(p_vars->mlx_ptr, p_vars->win_ptr,
		p_vars->img, 0, 0);
	draw_vecs(p_vars, p_vars->mlx_ptr, p_vars->win_ptr);
	return (0);
}

int	mv_origin(t_vars *p_vars)
{
	if (0 > p_vars->toggle_z)
	{
		if (65361 == p_vars->code)
			p_vars->originx += (4 / p_vars->scale);
		if (65362 == p_vars->code)
			p_vars->originy += (4 / p_vars->scale);
		if (65363 == p_vars->code)
			p_vars->originx -= (4 / p_vars->scale);
		if (65364 == p_vars->code)
			p_vars->originy -= (4 / p_vars->scale);
	}
	else
	{
		if (65362 == p_vars->code && p_vars->z_s > 1)
			p_vars->z_s -= 0.001;
		if (65364 == p_vars->code && p_vars->z_s < 9)
			p_vars->z_s += 0.001;
	}
	return (0);
}
