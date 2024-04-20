#ifndef FDF_H
#define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

typedef struct
{
	double	x;
	double	y;
	double	z;
} t_vec;

typedef struct
{
	int		xaxis;
	int		yaxis;
	t_vec	**map_vec;
} t_maps;

typedef struct
{
	double	g;
	double	x;
	double	y;
	int		iter;
	int		colour;
} t_edge;

int		init_arrs(t_maps *maps);
void	init_zaxis(t_maps *maps, char *filename);
void	free_2d_arr(char **arr);
void	printgrid(t_maps *maps);
double	gradient(double x, double x2, double y, double y2);
void	calc_vect(t_maps *maps, double cell);
void	calc_axes(t_maps *maps, char *filename);
void	draw_vecs(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_y_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
int		mod_rgb(int val, int n);

#endif
