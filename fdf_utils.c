#include "fdf.h"

double	gradient(double x, double x2, double y, double y2)
{
	return ((y2 - y) / (x2 - x));
}

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
			mlx_pixel_put(mlx_ptr, win_ptr, (int)maps->map_vec[i][j].x, (int)maps->map_vec[i][j].y, 0x00FFFFFF); //0x00888825
			j++;
		}
		i++;
	}
}

void	calc_vect(t_maps *maps, t_vars *p_vars)
{
	t_vec	origin;
	int		i;
	int		j;
	
	origin.x = p_vars->originx;
	origin.y = p_vars->originy;
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			maps->map_vec[i][j].x = origin.x + (j * p_vars->scale);
			maps->map_vec[i][j].y = origin.y + (j * (p_vars->scale / 2)) + (maps->map_vec[i][j].z * -1 * (p_vars->scale / p_vars->z_scale)); // rather than 2 multiply by #define SCALE
			maps->map_vec[i][j].y_o = origin.y + (j * (p_vars->scale / 2));
			j++;
		} 
		origin.x -= (p_vars->scale);
		origin.y += (p_vars->scale / 2); // /2
		i++;
	}
}

int	calc_axes(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = read_map(&r_vars, filename);
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
	free(r_vars.line);
	free_p(r_vars.p_line);
	close(r_vars.fd);
	return (0);
}

int	read_map(t_read *r_vars, char *filename)
{
	r_vars->fd = open(filename, O_RDONLY);
	return (r_vars->fd);
}
void	free_2d_arr(t_maps *map)
{
	int	i;

	i = 0;
	while (i < map->yaxis)
	{
		free(map->map_vec[i]);
		i++;
	}
	free(map->map_vec);
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

void	init_zaxis(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = open(filename, O_RDONLY);
	r_vars.i = 0;
	while (r_vars.i < maps->yaxis)
	{
		r_vars.line = get_next_line(r_vars.fd);
		r_vars.p_line = ft_split(r_vars.line, ' ');
		r_vars.j = 0;
		while (r_vars.j < maps->xaxis)
		{
			maps->map_vec[r_vars.i][r_vars.j].z = ft_atoi(r_vars.p_line[r_vars.j]);
			r_vars.j++;
		}
		free(r_vars.line);
		free_p(r_vars.p_line);
		r_vars.i++;
	}
	close(r_vars.fd);
}

void	free_p(char **p_line)
{
	int	i;

	i = 0;
	while (p_line[i])
	{
		free(p_line[i]);
		i++;
	}
	free(p_line);
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

void	draw_x_plane(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;
	
	ed.i = 0;
	while (ed.i < maps->yaxis)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis - 1)
		{
			ed.g_o = gradient(maps->map_vec[ed.i][ed.j].x, maps->map_vec[ed.i][ed.j + 1].x,
					maps->map_vec[ed.i][ed.j].y_o, maps->map_vec[ed.i][ed.j + 1].y_o);
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y_o = maps->map_vec[ed.i][ed.j].y_o;
			while (ed.x < maps->map_vec[ed.i][ed.j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y_o, 0x00003300);
				ed.x++;
				ed.y_o += ed.g_o;
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

void	draw_y_plane(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	t_edge	ed;

	ed.i = 0;
	while (ed.i < maps->yaxis - 1)
	{
		ed.j = 0;
		while (ed.j < maps->xaxis)
		{
			ed.g_o = gradient(maps->map_vec[ed.i][ed.j].y_o, maps->map_vec[ed.i + 1][ed.j].y_o,
					maps->map_vec[ed.i][ed.j].x, maps->map_vec[ed.i + 1][ed.j].x);		
			ed.x = maps->map_vec[ed.i][ed.j].x;
			ed.y_o = maps->map_vec[ed.i][ed.j].y_o;
			while (ed.y_o < maps->map_vec[ed.i + 1][ed.j].y_o)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y_o, 0x00003300);
				ed.x+= ed.g_o;
				ed.y_o++;
			}
			ed.j++;
		}
		ed.i++;
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






