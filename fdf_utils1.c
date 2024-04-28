#include "fdf.h"

double	gradient(double x, double x2, double y, double y2)
{
	return ((y2 - y) / (x2 - x));
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
			ed.g = gradient(maps->map_vec[ed.i][ed.j].x, maps->map_vec[ed.i][ed.j + 1].x,
					maps->map_vec[ed.i][ed.j].y, maps->map_vec[ed.i][ed.j + 1].y);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.x < maps->map_vec[ed.i][ed.j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, 0x00FFFFCC);
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

	ed.i = 0;
	while (ed.i < maps->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis)
		{
			ed.g = gradient(maps->map_vec[ed.i][ed.j].y, maps->map_vec[ed.i + 1][ed.j].y,
					maps->map_vec[ed.i][ed.j].x, maps->map_vec[ed.i + 1][ed.j].x);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y = maps->map_vec[ed.i][ed.j].y;
			while (ed.y < maps->map_vec[ed.i + 1][ed.j].y)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, 0x00FFFFCC);
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


// int	pix_colour(int val, t_maps *maps, t_edge *ed)
// {
// 	int	alpha; 
// 	int	red;
// 	int	green; 
// 	int	blue; 
//
// 	alpha =	(val >> 24) & 0xFF;
// 	red = (val >> 16) & 0xFF;
// 	green =	(val >> 8) & 0xFF;
// 	blue = val & 0xFF;
//
// 	printf("%f - %f\n", ed->y, ed->y_o);
//
// 	if (green < 255)
// 	 	green += (ed->y_o - ed->y) * maps->c;
// 	if (blue < 255)
// 		blue += (ed->y_o - ed->y) * maps->c;
//
// 	val = (alpha << 24) | (red << 16) | (green << 8) | blue; 
//
// 	return (val);
// }
//
// int	mod_rgb(int val, double n, int dr)
// {
// 	int	alpha; 
//     int	red;
//     int	green; 
//     int	blue; 
//
// 	n *= -1;
//
// 	alpha =	(val >> 24) & 0xFF;
// 	red = (val >> 16) & 0xFF;
// 	green =	(val >> 8) & 0xFF;
// 	blue = val & 0xFF;
// 	
// 	if (green < 255)
// 		green += n;
// 	if (blue < 255)
// 		blue += n;
//
// 	val = (alpha << 24) | (red << 16) | (green << 8) | blue; 
//
// 	return (val);
// }
//
// // calculate largest and smalest z value
// void	scale(t_maps *maps)
// {
// 	int	i;
// 	int	j;
//
// 	maps->l = maps->map_vec[0][0].z;
// 	maps->s = maps->map_vec[0][0].z;
// 	i = 0;
// 	while (i < maps->yaxis)
// 	{
// 		j = 0;
// 		while (j < maps->xaxis)
// 		{
// 			if ((double)(maps->map_vec[i][j].z) > maps->l)
// 				maps->l = (double)maps->map_vec[i][j].z;
// 			if ((double)(maps->map_vec[i][j].z) < maps->s)
// 				maps->s = (double)maps->map_vec[i][j].z;
// 			j++;
// 		}
// 		i++;
// 	}
//
// }
//
// // calculate scaling of z axis to colour gradient
// void	c_scale(t_maps *maps)
// {
// 	if (maps->l < 0)
// 		maps->l *= -1;
// 	if (maps->s < 0)
// 		maps->s *= -1;
// 	maps->l = maps->l + maps->s;
// 	maps->c = 255 / maps->l;
// }
//
// void	printgrid(t_maps *maps)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	j = 0;
// 	while (i < 8)
// 	{
// 		j = 0;
// 		while (j < 8)
// 		{
// 			printf("<%f>", maps->map_vec[i][j].z);
// 			j++;
// 		}
// 		i++;
// 		printf("\n");
// 	}
// }






