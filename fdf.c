#include "fdf.h"
#include <X11/Xlib.h>

// -lm required to link math library
// cc fdf.c fdf_utils0.c fdf_utils1.c fdf_utils2.c fdf_utils3.c 
// 		-L ./lib/ -lft -lmlx -lXext -lX11 -lm
// man -M ../man/ mlx_loop
// valgrind --trace-children=yes ./a.out ../maps/test_maps/t1.fdf

int	main(int argc, char **argv)
{
	t_maps	maps;
	t_vars	p_vars;
	int		err;

	err = 0;
	if (argc != 2)
		return (0);
	if (!(ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]))))
		return (0);
	init_vars(&p_vars, &maps);
	err += calc_axes(&maps, argv[1]);
	err += init_arrs(&maps);
	err += init_zaxis(&maps, argv[1]);
	if (err < 0)
		return (0);
	calc_vect(&maps, &p_vars);
	p_vars.mlx_ptr = mlx_init();
	p_vars.win_ptr = mlx_new_window(p_vars.mlx_ptr, 1200, 800, "cpt");
	
	// Display *display = XOpenDisplay(NULL);
	// Atom wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
	// ft_printf("<%d>", (long)wmDeleteWindow);

	draw(&p_vars);
	mlx_hook(p_vars.win_ptr, 3, 1L<<1, &key_up, &p_vars);
	mlx_hook(p_vars.win_ptr, 2, 1L<<0, &key_down, &p_vars);
	mlx_hook(p_vars.win_ptr, DestroyNotify, StructureNotifyMask, &terminator, &p_vars);
	mlx_loop_hook(p_vars.mlx_ptr, &loop_actions, &p_vars);
	mlx_loop(p_vars.mlx_ptr);

	return (0);
}

void	init_vars(t_vars *p_vars, t_maps *maps)
{
	p_vars->m = maps;
	p_vars->scale = 8;
	p_vars->originx = 1200.0;
	p_vars->originy = 200.0;
	p_vars->toggle_plane = -1;
	p_vars->toggle_grid = 1;
	p_vars->toggle_key = 0;
	p_vars->z_scale = 2;
	p_vars->toggle_z = -1;
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
			maps->map_vec[i][j].y = org.y + (j * (p_vars->scale / 2)) +
				(maps->map_vec[i][j].z * -1 *
					(p_vars->scale / p_vars->z_scale));
			maps->map_vec[i][j].y_o = org.y + (j * (p_vars->scale / 2));
			j++;
		} 
		org.x -= (p_vars->scale);
		org.y += (p_vars->scale / 2);
		i++;
	}
}

int	terminator(t_vars *p_vars)
{
	ft_printf("Hasta la vista, baby!");
	free_2d_arr(p_vars->m);
	mlx_destroy_window(p_vars->mlx_ptr, p_vars->win_ptr);
	free(p_vars->mlx_ptr);
	exit(0);
}

