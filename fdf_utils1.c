/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:51:33 by lworden           #+#    #+#             */
/*   Updated: 2024/05/05 21:24:29 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	gradient(double x, double x2, double y, double y2)
{
	if (!(0 == x2 - x))
		return ((y2 - y) / (x2 - x));
	else
		return (1);
}

void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed.col = 0x00FFFFCC;
	ed.i = 0;
	while (ed.i < maps->yaxis)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis - 1)
		{
			ed_setup(maps, &ed, 0);
			ed.g = gradient(ed.exx, ed.exx2, ed.eyy, ed.exy2);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.x < maps->map_vec[ed.i][ed.j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, ed.col);
				ed.x += 0.5;
				ed.y += ed.g / 2;
			}
			ed.j++;
		}
		ed.i++;
	}
}

void	draw_y_edges(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed.col = 0x00FFFFCC;
	ed.i = 0;
	while (ed.i < maps->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis)
		{
			ed_setup(maps, &ed, 1);
			ed.g = gradient(ed.eyy, ed.eyy2, ed.exx, ed.eyx2);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.y < maps->map_vec[ed.i + 1][ed.j].y)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, ed.col);
				ed.x += ed.g / 2;
				ed.y += 0.5;
			}
			flat_flip(maps, &ed, mlx_ptr, win_ptr);
			ed.j++;
		}
		ed.i++;
	}
}

void	ed_setup(t_maps *maps, t_edge *ed, int key)
{
	ed->exx = maps->map_vec[ed->i][ed->j].x;
	ed->eyy = maps->map_vec[ed->i][ed->j].y;
	ed->yy = maps->map_vec[ed->i][ed->j].y_o;
	if (0 == key)
	{
		ed->exx2 = maps->map_vec[ed->i][ed->j + 1].x; 
		ed->exy2 = maps->map_vec[ed->i][ed->j + 1].y;
		ed->xy2 = maps->map_vec[ed->i][ed->j + 1].y_o;
	}
	if (1 == key)
	{
		ed->eyy2 = maps->map_vec[ed->i + 1][ed->j].y;
		ed->eyx2 = maps->map_vec[ed->i + 1][ed->j].x;
		ed->yy2 = maps->map_vec[ed->i + 1][ed->j].y_o;
	}
}
