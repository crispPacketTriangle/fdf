/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:02:02 by lworden           #+#    #+#             */
/*   Updated: 2024/05/12 00:01:25 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/Xlib.h>

typedef struct t_read
{
	int		fd;
	char	*line;
	char	**p_line;
	int		i;
	int		j;
}	t_read;

typedef struct t_vec
{
	double	y_o;
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct t_maps
{
	int		xaxis;
	int		yaxis;
	t_vec	**map_vec;
}	t_maps;

typedef struct t_edge
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
	double	exx;
	double	exx2;
	double	exy2;
	double	eyy;
	double	eyy2;
	double	eyx2;
	double	yy;
	double	xy2;
	double	yy2;
}	t_edge;

typedef struct t_vars
{
	double	originx;
	double	originy;
	double	scale;
	double	z_s;
	int		height;
	int		width;
	int		toggle_grid;
	int		toggle_plane;
	int		toggle_z;
	int		toggle_key;
	int		code;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		dark_green;
	int		black;
	int		white;
	t_maps	*m;

}	t_vars;

void	init_vars(t_vars *p_vars, t_maps *maps);
int		init_arrs(t_maps *maps);
int		init_zaxis(t_maps *maps, char *filename);
void	flush_gnl(t_read *r_vars);
int		key_up(int keycode, t_vars *vars);
int		key_down(int keycode, t_vars *p_vars);
int		draw(t_vars *p_vars);
int		mv_origin(t_vars *p_vars);
int		loop_actions(t_vars *p_vars);
int		init_map(t_maps *maps, t_vars *p_vars, char *argv[]);
int		terminator(t_vars *p_vars);
void	g_f_s(int keycode, t_vars *p_vars);
void	free_2d_arr(t_maps *map);
void	free_p(char **p_line);
double	gradient(double x, double x2, double y, double y2);
void	calc_vect(t_maps *maps, t_vars *p_vars);
int		calc_axes(t_maps *maps, char *filename);
void	free_all(t_read *r_vars, int end);
void	draw_vecs(t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	draw_x_edges(t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	draw_y_edges(t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	flat_flip(t_vars *p_vars, t_edge *ed, void *mlx_ptr, void *win_ptr);
void	flip_y_edge(t_edge *ed, t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	draw_x_plane(t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	draw_y_plane(t_vars *p_vars, void *mlx_ptr, void *win_ptr);
void	ed_setup(t_maps *maps, t_edge *ed, int key);

void	draw_image(t_vars *p_vars, double x, double y, int color);
void	fill(t_vars *p_vars, char *addr);

#endif
