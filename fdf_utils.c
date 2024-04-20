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
			mlx_pixel_put(mlx_ptr, win_ptr, (int)maps->map_vec[i][j].x, (int)maps->map_vec[i][j].y, 0x00888825);
			j++;
		}
		i++;
	}
}

void	calc_vect(t_maps *maps, double cell)
{
	t_vec	origin;
	int		i;
	int		j;
	
	origin.x = 1200;
	origin.y = 200;
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			maps->map_vec[i][j].x = origin.x + (j * cell);
			maps->map_vec[i][j].y = origin.y + (j * (cell / 2)) + (maps->map_vec[i][j].z * -1 * 1.5); // rather than 2 multiply by #define SCALE
			maps->map_vec[i][j].y_o = origin.y + (j * (cell / 2));
			j++;
		} 
		origin.x -= (cell);
		origin.y += (cell / 2); // /2
		i++;
	}
}

// did i perhaps include an older version of gnl when I added
// gnl and ft_printf to libft?
int	calc_axes(t_maps *maps, char *filename)
{
	int		fd;
	char	*line;
	char	**p_line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	p_line = ft_split(line, ' ');
	maps->xaxis = 0;
	i = 0;
	while (p_line[i])
	{
		i++;
		maps->xaxis++;
	}
	maps->yaxis = 0;
	while (line)
	{
		maps->yaxis++;
		line = get_next_line(fd);
		printf("%s", line);
	}
	free(p_line);
	close(fd);
	return (0);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
	}
	free(arr);
}

// creates two 2D arrays
// grid:	tile identifier
// map_vec:	tile coordinates
int	init_arrs(t_maps *maps)
{
	int	i;

	maps->map_vec = malloc(maps->yaxis * sizeof(t_vec *));
	if (!maps->map_vec)
		return (1);
	i = 0;
	while (i < maps->yaxis)
	{
		maps->map_vec[i] = malloc(maps->xaxis * sizeof(t_vec));
		if (!maps->map_vec[i])
			return (1);
		i++;
	}
	return (0);
}

void	init_zaxis(t_maps *maps, char *filename)
{	
	char	*line;
	char	**p_line;
	int		fd;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	//line = get_next_line(fd);
	i = 0;
	while (i < maps->yaxis)
	{
		line = get_next_line(fd);
		
		p_line = ft_split(line, ' ');
		
		j = 0;
		while (j < maps->xaxis)
		{
			//printf("%s\n", p_line[j]);
			maps->map_vec[i][j].z = ft_atoi(p_line[j]);
			j++;
		}
		i++;
	}
	close(fd);
}

// no implementation for double type in ft_printf
void	printgrid(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			printf("<%f>", maps->map_vec[i][j].z);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr)
{
	int		i;
	int		j;
	int		dr;
	t_edge	ed;
	
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis - 1)
		{
			ed.colour = 0x000000FF;
			ed.g = gradient(maps->map_vec[i][j].x, maps->map_vec[i][j + 1].x, maps->map_vec[i][j].y, maps->map_vec[i][j + 1].y);
			ed.g_o = gradient(maps->map_vec[i][j].x, maps->map_vec[i][j + 1].x, maps->map_vec[i][j].y_o, maps->map_vec[i][j + 1].y_o);
			ed.x = maps->map_vec[i][j].x;
			ed.y = maps->map_vec[i][j].y;
			ed.y_o = maps->map_vec[i][j].y_o;
			while (ed.x < maps->map_vec[i][j + 1].x)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y_o, ed.colour);
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, 0x00FFFFFF);
				ed.x++;
				ed.y += ed.g;
				ed.y_o += ed.g_o;
			}
			j++;
		}
		i++;
	}
}

double	c_value(t_edge *ed, t_maps *maps, int i, int j)
{
	double	rel_z;
	
	rel_z = maps->map_vec[i][j].y_o + ed->y - ed->y_o;

	return (rel_z);
}

void	draw_y_edges(t_maps *maps, void * mlx_ptr, void *win_ptr)
{
	int		i;
	int		j;
	t_edge	ed;

	i = 0;
	while (i < maps->yaxis - 1)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			ed.colour = 0x000000FF;
			ed.g_o = gradient(maps->map_vec[i][j].y_o, maps->map_vec[i + 1][j].y_o, maps->map_vec[i][j].x, maps->map_vec[i + 1][j].x);		
			ed.x = maps->map_vec[i][j].x;
			ed.y_o = maps->map_vec[i][j].y_o;
			while (ed.y_o < maps->map_vec[i + 1][j].y_o)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y_o, ed.colour);
				ed.x+= ed.g_o;
				ed.y_o++;
			}
			
			ed.g = gradient(maps->map_vec[i][j].y, maps->map_vec[i + 1][j].y, maps->map_vec[i][j].x, maps->map_vec[i + 1][j].x);
			ed.x = maps->map_vec[i][j].x;
			ed.y = maps->map_vec[i][j].y;

			while (ed.y < maps->map_vec[i + 1][j].y)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, 0x00FFFFFF);
				ed.x+= ed.g;
				ed.y++;
			}
			// does this apply in some cases to the x axis too?
			if (maps->map_vec[i][j].y > maps->map_vec[i + 1][j].y)
			{
				while (ed.x > maps->map_vec[i + 1][j].x)
				{
					mlx_pixel_put(mlx_ptr, win_ptr, (int)ed.x, (int)ed.y, 0x00FFFFFF);
					ed.x-= ed.g;
					ed.y--;
				}
			}

			j++;
		}
		i++;
	}
}

int	pix_colour(int val, t_maps *maps, t_edge *ed)
{
	int	alpha; 
	int	red;
	int	green; 
	int	blue; 

	alpha =	(val >> 24) & 0xFF;
	red = (val >> 16) & 0xFF;
	green =	(val >> 8) & 0xFF;
	blue = val & 0xFF;

	printf("%f - %f\n", ed->y, ed->y_o);

	if (green < 255)
	 	green += (ed->y_o - ed->y) * maps->c;
	if (blue < 255)
		blue += (ed->y_o - ed->y) * maps->c;

	val = (alpha << 24) | (red << 16) | (green << 8) | blue; 

	return (val);
}

int	mod_rgb(int val, double n, int dr)
{
	int	alpha; 
    int	red;
    int	green; 
    int	blue; 

	n *= -1;

	alpha =	(val >> 24) & 0xFF;
	red = (val >> 16) & 0xFF;
	green =	(val >> 8) & 0xFF;
	blue = val & 0xFF;
	
	if (green < 255)
		green += n;
	if (blue < 255)
		blue += n;

	val = (alpha << 24) | (red << 16) | (green << 8) | blue; 

	return (val);
}

// calculate largest and smalest z value
void	scale(t_maps *maps)
{
	int	i;
	int	j;

	maps->l = maps->map_vec[0][0].z;
	maps->s = maps->map_vec[0][0].z;
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			if ((double)(maps->map_vec[i][j].z) > maps->l)
				maps->l = (double)maps->map_vec[i][j].z;
			if ((double)(maps->map_vec[i][j].z) < maps->s)
				maps->s = (double)maps->map_vec[i][j].z;
			j++;
		}
		i++;
	}

}

// calculate scaling of z axis to colour gradient
void	c_scale(t_maps *maps)
{
	if (maps->l < 0)
		maps->l *= -1;
	if (maps->s < 0)
		maps->s *= -1;
	maps->l = maps->l + maps->s;
	maps->c = 255 / maps->l;
}







