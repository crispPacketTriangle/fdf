#include "fdf.h"

// -lm required to link math library
// cc fdf.c fdf_utils.c -L ./lib/ -lft -lmlx -lXext -lX11 -lm
// man -M ../man/ mlx_loop
// valgrind --trace-children=yes ./a.out ../maps/test_maps/t1.fdf

// possible error handling if axes not even

int	key_hook(int keycode, t_vars *vars);
int	draw(t_vars *p_vars);
int	mv_origin(t_vars *p_vars);
int	key_down(int keycode, t_vars *p_vars);
int	loop_actions(t_vars *p_vars);

int	main(int argc, char **argv)
{
	double	g;
	//void	*mlx_ptr;
	//void	*win_ptr;
	t_maps	maps;
	t_vars	p_vars;
	int		(*key_ptr)(int k, t_vars *p_vars);

	// redundant
	key_ptr = &key_hook;
	p_vars.m = &maps;
	p_vars.scale = 8;
	p_vars.originx = 1200.0;
	p_vars.originy = 200.0;
	p_vars.toggle_plane = -1;
	p_vars.toggle_grid = 1;
	p_vars.z_scale = 2;
	p_vars.toggle_z = -1;

	if (argc != 2)
	{
		return (0);
	}
	if (calc_axes(&maps, argv[1]))
		return (0);
	//ft_printf("x: %d\ny: %d\n", maps.xaxis, maps.yaxis);
	///////////////////////////////
	init_arrs(&maps);
	init_zaxis(&maps, argv[1]);
	calc_vect(&maps, &p_vars);
	//printf("-- %f\n", maps.map_vec[0][0].z);
	//printgrid(&maps);
	///////////////////////////////
	p_vars.mlx_ptr = mlx_init();
	p_vars.win_ptr = mlx_new_window(p_vars.mlx_ptr, 1200, 800, "cpt");
	//draw_x_plane(&maps, p_vars.mlx_ptr, p_vars.win_ptr);
	//draw_y_plane(&maps, p_vars.mlx_ptr, p_vars.win_ptr);
	draw(&p_vars);
	//scale(&maps);
	//c_scale(&maps);

	//draw_x_edges(&maps, p_vars.mlx_ptr, p_vars.win_ptr);
	//draw_y_edges(&maps, p_vars.mlx_ptr, p_vars.win_ptr);
	//draw_vecs(&maps, p_vars.mlx_ptr, p_vars.win_ptr);

	// this hook takes the arguments 3 and a bit mask, which means listen specifically
	// for a key up event
	mlx_hook(p_vars.win_ptr, 3, 1L<<1, &key_hook, &p_vars);
	mlx_hook(p_vars.win_ptr, 2, 1L<<0, &key_down, &p_vars);
	// currently callng draw function every time through loop
	//mlx_loop_hook(p_vars.mlx_ptr, &draw, &p_vars);

	mlx_loop_hook(p_vars.mlx_ptr, &loop_actions, &p_vars);


	// initialises a loop where the window is refreshed and listens for events
	mlx_loop(p_vars.mlx_ptr);
	// this is creating a hook into the loop in order to terminate it presumably
	// since the window is like a mini server that we can call into, hook into?
	// or just to be able to call a function? like the main logic of the programme
	// is passed here? exactly this is how we call continuely in the loop
	//
	// int		mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param);
	//
	// seems like a function pointer is passed and also a pointer that should point
	// to a struct that is then passed into the function inside mlx_loop_hook()

	//mlx_loop_hook(p_vars.mlx_ptr, &draw, &p_vars);


	//mlx_key_hook(vars.win, key_hook, &vars);

	free_2d_arr(maps.map_vec);

	//mlx_destroy_window(p_vars.mlx_ptr, p_vars.win_ptr);	
}

// called when key up
int	key_hook(int keycode, t_vars *p_vars)
{
	// test keycode on different machines, could vary
	//printf("%d\n", keycode);
	if (65307 == keycode)
	{
		// todo: free objects
		mlx_destroy_window(p_vars->mlx_ptr, p_vars->win_ptr);
		free(p_vars->mlx_ptr);
		exit(0);
	}
	if (102 == keycode)
	{
		p_vars->toggle_plane *= -1;
		draw(p_vars);
	}
	if (103 == keycode)
	{
		p_vars->toggle_grid *= -1;
		draw(p_vars);
	}
	if (105 == keycode)
	{
		p_vars->scale+=2;
		draw(p_vars);
	}
	if (111 == keycode)
	{
		if ((p_vars->scale - 2) > 0)
		{
			p_vars->scale-=2;
			draw(p_vars);
		}
	}
	p_vars->toggle_key = 0;
	if (115 == keycode)
		p_vars->toggle_z = -1;
	return (0);
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

// function called when any key pressed down 
int	key_down(int keycode, t_vars *p_vars)
{
	if (115 == keycode)
		p_vars->toggle_z *= -1;
	if (65361 == keycode || 65362 == keycode || 65363 == keycode || 65364 == keycode)
	{
		p_vars->toggle_key = 1;
		p_vars->code = keycode;
	}
	return(0);
}

// called at every iteration through loop
int	loop_actions(t_vars *p_vars)
{
	if (1 == p_vars->toggle_key)
	{
		mv_origin(p_vars);
		draw(p_vars);
	}
	return (0);
}

