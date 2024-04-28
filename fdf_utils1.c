#include "fdf.h"

double	gradient(double x, double x2, double y, double y2)
{
	double	gr;

	if (!(0 == x2 - x))
		return ((y2 - y) / (x2 - x));
	else
	{
		gr = (y2 > y) ? INFINITY : -INFINITY;
		return (gr);
	}
}

void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;
	
	ed.i = 0;
	while (ed.i < maps->yaxis)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis - 1)
		{
			ed.g = gradient(maps->map_vec[ed.i][ed.j].x,
					maps->map_vec[ed.i][ed.j + 1].x, 
						maps->map_vec[ed.i][ed.j].y,
							maps->map_vec[ed.i][ed.j + 1].y);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.x < maps->map_vec[ed.i][ed.j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y,
						0x00FFFFCC);
				ed.x++;
				ed.y += ed.g;
			}
			ed.j++;
		}
		ed.i++;
	}
}

void	draw_y_edges(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed_setup(&ed, 0x00FFFFCC);
	while (ed.i < maps->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis)
		{
			ed.g = gradient(maps->map_vec[ed.i][ed.j].y, 
					maps->map_vec[ed.i + 1][ed.j].y, maps->map_vec[ed.i]
						[ed.j].x, maps->map_vec[ed.i + 1][ed.j].x);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.y < maps->map_vec[ed.i + 1][ed.j].y)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, ed.col);
				ed.x+= ed.g;
				ed.y++;
			}
			if (maps->map_vec[ed.i][ed.j].y > maps->map_vec[ed.i + 1][ed.j].y)
				flip_y_edge(&ed, maps, mlx_ptr, win_ptr);
			ed.j++;
		}
		ed.i++;
	}
}

void	flip_y_edge(t_edge *ed, t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	while (ed->x > maps->map_vec[ed->i + 1][ed->j].x)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, (int)ed->x, (int)ed->y, 0x00FFFFCC);
		ed->x-= ed->g;
		ed->y--;
	}
}

void	ed_setup(t_edge *ed, int col)
{
	ed->i = 0;
	ed->col = col;
}

