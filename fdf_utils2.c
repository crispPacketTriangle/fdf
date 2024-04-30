#include "fdf.h"

void	draw_vecs(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, (int)maps->map_vec[i][j].x,
					(int)maps->map_vec[i][j].y, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_x_plane(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;
	
	ed_setupold(&ed, 0x00003300);
	while (ed.i < maps->yaxis)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis - 1)
		{
			ed.g_o = gradient(maps->map_vec[ed.i][ed.j].x,
					maps->map_vec[ed.i][ed.j + 1].x, maps->map_vec[ed.i]
						[ed.j].y_o, maps->map_vec[ed.i][ed.j + 1].y_o);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y_o = maps->map_vec[ed.i][ed.j].y_o;
			while (ed.x < maps->map_vec[ed.i][ed.j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr,
						(int)ed.x, (int)ed.y_o, ed.col);
				ed.x++;
				ed.y_o += ed.g_o;
			}
			ed.j++;
		}
		ed.i++;
	}
}

void	draw_y_plane(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed_setupold(&ed, 0x00003300);
	while (ed.i < maps->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis)
		{
			ed.g_o = gradient(maps->map_vec[ed.i][ed.j].y_o,
					maps->map_vec[ed.i + 1][ed.j].y_o, maps->map_vec[ed.i]
						[ed.j].x, maps->map_vec[ed.i + 1][ed.j].x);		
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y_o = maps->map_vec[ed.i][ed.j].y_o;
			while (ed.y_o < maps->map_vec[ed.i + 1][ed.j].y_o)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x,
						(int)ed.y_o, ed.col);
				ed.x+= ed.g_o;
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
	mlx_clear_window(p_vars->mlx_ptr, p_vars->win_ptr);
	if (0 < p_vars->toggle_plane)
	{
		draw_x_plane(p_vars->m, p_vars->mlx_ptr, p_vars->win_ptr);
		draw_y_plane(p_vars->m, p_vars->mlx_ptr, p_vars->win_ptr);
	}
	if (0 < p_vars->toggle_grid)
	{
		draw_x_edges(p_vars->m, p_vars->mlx_ptr, p_vars->win_ptr);
		draw_y_edges(p_vars->m, p_vars->mlx_ptr, p_vars->win_ptr);
	}
	draw_vecs(p_vars->m, p_vars->mlx_ptr, p_vars->win_ptr);
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
		if (65362 == p_vars->code && p_vars->z_scale > 1)
			p_vars->z_scale -= 0.001;
		if (65364 == p_vars->code && p_vars->z_scale < 9)
			p_vars->z_scale += 0.001;
	}
	return(0);
}

// x_plane
// maps->map_vec[ed.i][ed.j].x,
// maps->map_vec[ed.i][ed.j + 1].x, 
// maps->map_vec[ed.i][ed.j].y_o, 
// maps->map_vec[ed.i][ed.j + 1].y_o
//
// y_plane
// maps->map_vec[ed.i][ed.j].y_o,
// maps->map_vec[ed.i + 1][ed.j].y_o, 
// maps->map_vec[ed.i][ed.j].x, 
// maps->map_vec[ed.i + 1][ed.j].x
//
//
