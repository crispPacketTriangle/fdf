#include "fdf.h"

int	key_up(int keycode, t_vars *p_vars)
{
	if (65307 == keycode)
	{
		free_2d_arr(p_vars->m);
		mlx_destroy_window(p_vars->mlx_ptr, p_vars->win_ptr);
		free(p_vars->mlx_ptr);
		exit(0);
	}

	g_f_s(p_vars, keycode);
	p_vars->toggle_key = 0;
	if (115 == keycode)
		p_vars->toggle_z = -1;
	return (0);
}

void	g_f_s(t_vars *p_vars, int keycode)
{
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
		p_vars->scale += 2;
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
}

int	key_down(int keycode, t_vars *p_vars)
{
	if (115 == keycode)
		p_vars->toggle_z *= -1;
	if (65361 == keycode || 65362 == keycode ||
			65363 == keycode || 65364 == keycode)
	{
		p_vars->toggle_key = 1;
		p_vars->code = keycode;
	}
	return(0);
}

int	loop_actions(t_vars *p_vars)
{
	if (1 == p_vars->toggle_key)
	{
		mv_origin(p_vars);
		draw(p_vars);
	}
	return (0);
}

void	free_2d_arr(t_maps *map)
{
	int	i;

	i = 0;
	while (i < map->yaxis)
	{
		free(map->map_vec[i]);
		i++;
	}
	free(map->map_vec);
}

