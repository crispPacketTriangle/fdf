#ifndef FDF_H
#define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct
{
	double	y_o;
	double	x;
	double	y;
	double	z;
} t_vec;

typedef struct
{
	double	l;
	double	s;
	double	c;
	int		xaxis;
	int		yaxis;
	t_vec	**map_vec;
} t_maps;

typedef struct
{
	double	g;
	double	g_o;
	double	x;
	double	x_o;
	double	y;
	double	y_o;
	int		colour;
} t_edge;

typedef struct
{
	double	originx;
	double	originy;
	double	scale;
	double	z_scale;
	int		toggle_grid;
	int		toggle_plane;
	int		toggle_z;
	int		toggle_key;
	int		code;
	void	*mlx_ptr;
	void	*win_ptr;
	t_maps	*m;

} t_vars;

int		init_arrs(t_maps *maps);
void	init_zaxis(t_maps *maps, char *filename);
void	free_2d_arr(t_vec **arr);
void	free_p(char **p_line);
void	printgrid(t_maps *maps);
double	gradient(double x, double x2, double y, double y2);
void	calc_vect(t_maps *maps, t_vars *p_vars);
int		calc_axes(t_maps *maps, char *filename);
void	draw_vecs(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_y_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_x_plane(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_y_plane(t_maps *maps, void *mlx_ptr, void *win_ptr);
int		mod_rgb(int val, double n, int dr);
int		pix_colour(int val, t_maps *maps, t_edge *ed);
void	c_scale(t_maps *maps);
void	scale(t_maps *maps);

#endif
