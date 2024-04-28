#include "fdf.h"

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

int	calc_axes(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = open(filename, O_RDONLY);
	r_vars.line = get_next_line(r_vars.fd);
	if (!(r_vars.line) || r_vars.fd < 0)
		return (-1);
	r_vars.p_line = ft_split(r_vars.line, ' ');
	r_vars.i = 0;
	while (r_vars.p_line[r_vars.i])
	{
		r_vars.i++;
		maps->xaxis++;
	}
	while (r_vars.line)
	{
		maps->yaxis++;
		free(r_vars.line);
		r_vars.line = get_next_line(r_vars.fd);
	}
	free(r_vars.line);
	free_p(r_vars.p_line);
	close(r_vars.fd);
	return (0);
}

int	init_arrs(t_maps *maps)
{
	int	i;
	
	maps->map_vec = malloc(maps->yaxis * sizeof(t_vec *));
	if (!maps->map_vec)
		return (-1);
	i = 0;
	while (i < maps->yaxis)
	{
		maps->map_vec[i] = malloc(maps->xaxis * sizeof(t_vec));
		if (!maps->map_vec[i])
			return (-1);
		i++;
	}
	return (0);
}

void	init_zaxis(t_maps *maps, char *filename)
{
	t_read	r_vars;

	r_vars.fd = open(filename, O_RDONLY);
	r_vars.i = 0;
	while (r_vars.i < maps->yaxis)
	{
		r_vars.line = get_next_line(r_vars.fd);
		r_vars.p_line = ft_split(r_vars.line, ' ');
		r_vars.j = 0;
		while (r_vars.j < maps->xaxis)
		{
			maps->map_vec[r_vars.i][r_vars.j].z =
				ft_atoi(r_vars.p_line[r_vars.j]);
			r_vars.j++;
		}
		free(r_vars.line);
		free_p(r_vars.p_line);
		r_vars.i++;
	}
	close(r_vars.fd);
}

void	free_p(char **p_line)
{
	int	i;

	i = 0;
	while (p_line[i])
	{
		free(p_line[i]);
		i++;
	}
	free(p_line);
}
