#include "fdf.h"

// cc fdf.c -L ./lib/ -lft -lmlx -lXext -lX11

int main(int argc, char **argv)
{
	double g;
	void *mlx_ptr;
	void *win_ptr;
	t_maps maps;

	if (argc != 2)
	{
		ft_printf("> provide a filename as a single argument\n");
		return (0);
	}
	calc_axes(&maps, argv[1]);
	// ft_printf("x: %d\ny: %d\n", maps.xaxis, maps.yaxis);
	///////////////////////////////
	init_arrs(&maps);
	init_zaxis(&maps, argv[1]);

	calc_vect(&maps, 5.0);
	// printf("-- %f\n", maps.map_vec[0][0].z);
	// printgrid(&maps);
	///////////////////////////////
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1600, 800, "cpt");

	draw_vecs(&maps, mlx_ptr, win_ptr);
	draw_x_edges(&maps, mlx_ptr, win_ptr);
	draw_y_edges(&maps, mlx_ptr, win_ptr);
	while (1)
	{
		// draw_vecs(&maps, mlx_ptr, win_ptr);
		// draw_x_edges(&maps, mlx_ptr, win_ptr);
		// draw_y_edges(&maps, mlx_ptr, win_ptr);
		// printf("<my fears are ephemeral and conquered by my doing>");
	}
	mlx_destroy_window(mlx_ptr, win_ptr);
}
