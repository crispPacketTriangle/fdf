#include "fdf.h"

// -lm required to link math library
// cc fdf.c fdf_utils.c -L ./lib/ -lft -lmlx -lXext -lX11 -lm

int	main(int argc, char **argv)
{
	double	g;
	void	*mlx_ptr;
	void	*win_ptr;
	t_maps	maps;
	
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
	calc_vect(&maps, 8.0);
	//printf("-- %f\n", maps.map_vec[0][0].z);
	//printgrid(&maps);
	///////////////////////////////
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2900, 1600, "cpt");
	
	//scale(&maps);
	//c_scale(&maps);
	draw_vecs(&maps, mlx_ptr, win_ptr);
	draw_x_edges(&maps, mlx_ptr, win_ptr);
	draw_y_edges(&maps, mlx_ptr, win_ptr);

	while (1)
	{
		//printf("<my fears are ephemeral and conquered by my doing>");
	}
	mlx_destroy_window(mlx_ptr, win_ptr);	
}

