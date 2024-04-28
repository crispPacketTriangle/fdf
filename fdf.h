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
	int		fd;
	char	*line;
	char	**p_line;
	int		i;
	int		j;
} t_read;

typedef struct
{
	double	y_o;
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
	int		col;
	int		i;
	int		j;
	double	g;
	double	g_o;
	double	x;
	double	x_o;
	double	y;
	double	y_o;
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

void	init_vars(t_vars *p_vars, t_maps *maps);
int		init_arrs(t_maps *maps);
int		init_zaxis(t_maps *maps, char *filename);
int		key_up(int keycode, t_vars *vars);
int		key_down(int keycode, t_vars *p_vars);
int		draw(t_vars *p_vars);
int		mv_origin(t_vars *p_vars);
int		loop_actions(t_vars *p_vars);
void	g_f_s(t_vars *p_vars, int keycode);
void	free_2d_arr(t_maps *map);
void	free_p(char **p_line);
double	gradient(double x, double x2, double y, double y2);
void	calc_vect(t_maps *maps, t_vars *p_vars);
int		calc_axes(t_maps *maps, char *filename);
void	free_all(t_read *r_vars, int end);
void	draw_vecs(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_x_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_y_edges(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	flip_y_edge(t_edge *ed, t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_x_plane(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	draw_y_plane(t_maps *maps, void *mlx_ptr, void *win_ptr);
void	ed_setup(t_edge *ed, int col);

#endif
