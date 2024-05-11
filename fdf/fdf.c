/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:27:28 by lworden           #+#    #+#             */
/*   Updated: 2024/05/11 21:47:28 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// -lm required to link math library
// cc fdf.c fdf_utils0.c fdf_utils1.c fdf_utils2.c fdf_utils3.c 
// 		-L ./lib/ -lft -lmlx -lXext -lX11 -lm
// man -M ../man/ mlx_loop
// valgrind --trace-children=yes ./a.out ../maps/test_maps/t1.fdf

int	main(int argc, char **argv)
{
	t_maps	maps;
	t_vars	p_vars;

	if (argc != 2)
		return (1);
	if (!(ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]))))
		return (1);
	p_vars.mlx_ptr = mlx_init();
	if (!p_vars.mlx_ptr)
		return (1);
	if (init_map(&maps, &p_vars, argv))
		return (1);
	calc_vect(&maps, &p_vars);
	p_vars.win_ptr = mlx_new_window(p_vars.mlx_ptr,
			p_vars.width, p_vars.height, "cpt");
	draw(&p_vars);
	mlx_hook(p_vars.win_ptr, 3, 1L << 1, &key_up, &p_vars);
	mlx_hook(p_vars.win_ptr, 2, 1L << 0, &key_down, &p_vars);
	mlx_hook(p_vars.win_ptr, 17, StructureNotifyMask, &terminator, &p_vars);
	mlx_loop_hook(p_vars.mlx_ptr, &loop_actions, &p_vars);
	mlx_loop(p_vars.mlx_ptr);
	return (0);
}

void	init_vars(t_vars *p_vars, t_maps *maps)
{
	p_vars->m = maps;
	p_vars->scale = 8;
	p_vars->height = 800;
	p_vars->width = 1200;
	p_vars->originx = 1200.0;
	p_vars->originy = 100.0;
	p_vars->toggle_plane = -1;
	p_vars->toggle_grid = 1;
	p_vars->toggle_key = 0;
	p_vars->z_s = 8;
	p_vars->toggle_z = -1;
	p_vars->img = mlx_new_image(p_vars->mlx_ptr, 1200, 800);
	p_vars->bits_per_pixel = 8;
	p_vars->size_line = 1200;
	p_vars->endian = 0;
	p_vars->addr = mlx_get_data_addr(p_vars->img, &p_vars->bits_per_pixel,
			&p_vars->size_line, &p_vars->endian);
	p_vars->dark_green = mlx_get_color_value(p_vars->mlx_ptr, 0x00003300);
	p_vars->white = mlx_get_color_value(p_vars->mlx_ptr, 0x00FFFFFF);
	p_vars->black = mlx_get_color_value(p_vars->mlx_ptr, 0x00000000);
	maps->xaxis = 0;
	maps->yaxis = 0;
}

void	calc_vect(t_maps *maps, t_vars *p_vars)
{
	t_vec	org;
	int		i;
	int		j;

	org.x = p_vars->originx;
	org.y = p_vars->originy;
	i = 0;
	while (i < maps->yaxis)
	{
		j = 0;
		while (j < maps->xaxis)
		{
			maps->map_vec[i][j].x = org.x + (j * p_vars->scale);
			maps->map_vec[i][j].y = org.y + (j * (p_vars->scale / 2))
				+ (maps->map_vec[i][j].z * -1 * (p_vars->scale / p_vars->z_s));
			maps->map_vec[i][j].y_o = org.y + (j * (p_vars->scale / 2));
			j++;
		}
		org.x -= (p_vars->scale);
		org.y += (p_vars->scale / 2);
		i++;
	}
}

int	init_map(t_maps *maps, t_vars *p_vars, char *argv[])
{
	init_vars(p_vars, maps);
	if (calc_axes(maps, argv[1]) < 0)
	{
		mlx_destroy_image(p_vars->mlx_ptr, p_vars->img);
		mlx_destroy_display(p_vars->mlx_ptr);
		free(p_vars->mlx_ptr);
		return (1);
	}
	if (init_arrs(maps) < 0)
	{
		mlx_destroy_image(p_vars->mlx_ptr, p_vars->img);
		mlx_destroy_display(p_vars->mlx_ptr);
		free(p_vars->mlx_ptr);
		free_2d_arr(maps);
		return (1);
	}
	if (init_zaxis(maps, argv[1]) < 0)
	{
		mlx_destroy_image(p_vars->mlx_ptr, p_vars->img);
		mlx_destroy_display(p_vars->mlx_ptr);
		free(p_vars->mlx_ptr);
		free_2d_arr(maps);
		return (1);
	}
	return (0);
}

int	terminator(t_vars *p_vars)
{
	ft_printf("Hasta la vista, baby!\n");
	free_2d_arr(p_vars->m);
	mlx_destroy_image(p_vars->mlx_ptr, p_vars->img);
	mlx_destroy_window(p_vars->mlx_ptr, p_vars->win_ptr);
	mlx_destroy_display(p_vars->mlx_ptr);
	free(p_vars->mlx_ptr);
	exit(0);
}
