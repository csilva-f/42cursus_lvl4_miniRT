/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 18:44:43 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdio.h>

void	init(t_mini *mini, char **argv)
{
	mini->file = argv[1];
	mini->is_valid = 1;
	mini->al = malloc(sizeof(t_al));
	mini->cam = malloc(sizeof(t_cam));
	mini->light = malloc(sizeof(t_light));
	mini->plane = malloc(sizeof(t_plane));
	mini->sp = malloc(sizeof(t_sphere));
	mini->cyl = malloc(sizeof(t_cylinder));
}

void	free_structs(t_mini *mini)
{
	free(mini->al);
	free(mini->cam);
	free(mini->light);
	free(mini->plane);
	free(mini->sp);
	free(mini->cyl);
}

void	check_identifier(t_mini *mini, char *str)
{
	if (ft_strncmp(str, "A", 2) && ft_strncmp(str, "C", 2) \
			&& ft_strncmp(str, "L", 2) && ft_strncmp(str, "pl", 3) \
			&& ft_strncmp(str, "sp", 3) && ft_strncmp(str, "cy", 3))
		mini->is_valid = 0;
}

int	rgb_to_int(int red, int green, int blue)
{
	int	res;

	res = (red * 65536) + (green * 256) + blue;
	return (res);
}

void	vars_errors(t_mini *mini, int code)
{
	error_handler(mini->is_valid, code);
	mini->is_valid = 0;
}

int	count_vars(char **vars, int equal, int code, t_mini *m)
{
	int	i;

	i = 0;
	while (vars[i] != 0 && ft_strncmp(vars[i], "\0", 1))
		i++;
	if ((i == equal) || (equal == 1 && i == 2))
		return (i);
	else
	{
		vars_errors(m, code);
		return (0);
	}
}

int	fill_colors(t_mini *m, char *str, int c)
{
	int		r;
	int		g;
	int		b;
	char	**color;

	color = ft_split(str, ',');
	if (count_vars(color, 3, 4, m))
	{
		if (ft_str_isd(color[0]) && ft_str_isd(color[1]) \
				&& ft_str_isd(color[2]))
		{
			r = ft_atoi(color[0]);
			g = ft_atoi(color[1]);
			b = ft_atoi(color[2]);
			if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
				c = rgb_to_int(r, g, b);
			else
				vars_errors(m, 4);
		}
		else
			vars_errors(m, 4);
	}
	ft_free_split(color);
	return (c);
}

float	float_check(t_mini *m, char *str)
{
	float	nbr;
	char	**parts;

	nbr = -1;
	parts = ft_split(str, '.');
	if (count_vars(parts, 1, 4, m) == 2)
	{
		if (ft_str_isd(parts[0]) && ft_str_isd(parts[1]))
			nbr = ft_atoi(parts[0]) + (float)ft_atoi(parts[1])
				/ powf(10, ft_strlen(parts[1]));
		else
			vars_errors(m, 4);
	}
	else if (count_vars(parts, 1, 4, m) == 1)
	{
		if (ft_str_isd(parts[0]))
			nbr = ft_atoi(parts[0]);
		else
			vars_errors(m, 4);
	}
	ft_free_split(parts);
	return (nbr);
}

void	check_a_vars(t_mini *m, char **vars)
{
	m->al->ratio = float_check(m, vars[1]);
	if (m->is_valid)
		m->al->color = fill_colors(m, vars[2], -1);
}

void	check_c_vars(t_mini *m, char **v)
{
	char	**data;

	data = ft_split(v[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->cam->x = float_check(m, data[0]);
		m->cam->y = float_check(m, data[1]);
		m->cam->z = float_check(m, data[2]);
		ft_free_split(data);
		data = ft_split(v[2], ',');
		if (count_vars(data, 3, 4, m))
		{
			m->cam->ov_x = float_check(m, data[0]);
			m->cam->ov_y = float_check(m, data[1]);
			m->cam->ov_z = float_check(m, data[2]);
			if (fabsf(m->cam->ov_x) > 1 || fabsf(m->cam->ov_y) > 1 \
					|| fabsf(m->cam->ov_y) > 1)
				vars_errors(m, 4);
			ft_free_split(data);
			if (ft_str_isd(v[3]) && ft_atoi(v[3]) <= 180 && ft_atoi(v[3]) >= 0)
				m->cam->fov = ft_atoi(v[3]);
			else
				vars_errors(m, 4);
		}
	}
}

void	check_l_vars(t_mini *m, char **vars)
{
	char	**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->light->x = float_check(m, data[0]);
		m->light->y = float_check(m, data[1]);
		m->light->z = float_check(m, data[2]);
		ft_free_split(data);
		if (m->is_valid)
		{
			m->light->ratio = float_check(m, vars[2]);
			if (m->light->ratio < 0 || m->light->ratio > 1)
				vars_errors(m, 4);
			else
				m->light->color = fill_colors(m, vars[3], -1);
		}
	}
}

void	check_pl_vars(t_mini *m, char **vars)
{
	char	**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->plane->x = float_check(m, data[0]);
		m->plane->y = float_check(m, data[1]);
		m->plane->z = float_check(m, data[2]);
		ft_free_split(data);
		data = ft_split(vars[2], ',');
		if (count_vars(data, 3, 4, m))
		{
			m->plane->nv_x = float_check(m, data[0]);
			m->plane->nv_y = float_check(m, data[1]);
			m->plane->nv_z = float_check(m, data[2]);
			ft_free_split(data);
			if (fabs(m->plane->nv_x) > 1 || fabs(m->plane->nv_y) > 1 \
				|| fabs(m->plane->nv_z) > 1)
				vars_errors(m, 4);
			else
				m->plane->color = fill_colors(m, vars[3], -1);
		}
	}
}

void	check_sp_vars(t_mini *m, char **vars)
{
	char	**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->sp->cx = float_check(m, data[0]);
		m->sp->cy = float_check(m, data[1]);
		m->sp->cz = float_check(m, data[2]);
		ft_free_split(data);
		m->sp->d = float_check(m, vars[2]);
		m->plane->color = fill_colors(m, vars[3], -1);
	}
}

void	check_cy_vars(t_mini *m, char **vars)
{
	char	**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->cyl->cx = float_check(m, data[0]);
		m->cyl->cy = float_check(m, data[1]);
		m->cyl->cz = float_check(m, data[2]);
		ft_free_split(data);
		data = ft_split(vars[2], ',');
		if (count_vars(data, 3, 4, m))
		{
			m->cyl->nv_x = float_check(m, data[0]);
			m->cyl->nv_y = float_check(m, data[1]);
			m->cyl->nv_z = float_check(m, data[2]);
			ft_free_split(data);
			if (fabs(m->cyl->nv_x) > 1 || fabs(m->cyl->nv_y) > 1 \
				|| fabs(m->cyl->nv_z) > 1)
				vars_errors(m, 4);
			else
			{
				m->cyl->d = float_check(m, vars[3]);
				m->cyl->h = float_check(m, vars[4]);
				m->cyl->color = fill_colors(m, vars[5], -1);
			}
		}
	}
}

void	check_line_values(t_mini *mini, char **vars)
{
	if (!ft_strncmp(vars[0], "A", 2))
	{
		if (count_vars(vars, 3, 5, mini))
			check_a_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "C", 2))
	{
		if (count_vars(vars, 4, 5, mini))
			check_c_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "L", 2))
	{
		if (count_vars(vars, 4, 5, mini))
			check_l_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "pl", 3))
	{
		if (count_vars(vars, 4, 5, mini))
			check_pl_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "sp", 3))
	{
		if (count_vars(vars, 4, 5, mini))
			check_sp_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "cy", 3))
	{
		if (count_vars(vars, 6, 5, mini))
			check_cy_vars(mini, vars);
	}
}

void	check_lines(t_mini *mini, char *aux)
{
	char	**vars;

	vars = ft_split(aux, ' ');
	check_identifier(mini, vars[0]);
	if (!mini->is_valid)
		error_handler(mini->is_valid, 3);
	else
		check_line_values(mini, vars);
	ft_free_split(vars);
}

void	get_values(t_mini *mini)
{
	char	*aux;

	mini->fd = open(mini->file, O_RDONLY);
	while (1)
	{
		aux = get_next_line(mini->fd);
		if (aux == NULL)
			break ;
		aux = ft_remove_lb(aux);
		check_lines(mini, aux);
		free(aux);
	}
	free(aux);
	printf("A-------------------\n%f  %i\n", mini->al->ratio, mini->al->color);
	printf("C-------------------\n%f,%f,%f  %f,%f,%f %i\n", mini->cam->x, mini->cam->y, mini->cam->z, \
			mini->cam->ov_x, mini->cam->ov_y, mini->cam->ov_z, mini->cam->fov);
	printf("L-------------------\n%f,%f,%f  %f, %i\n", mini->light->x, mini->light->y, \
			mini->light->z, mini->light->ratio, mini->light->color);
	printf("pl-------------------\n%f,%f,%f %f,%f,%f  %i\n", mini->plane->x, mini->plane->y, mini->plane->z, \
			mini->plane->nv_x, mini->plane->nv_y, mini->plane->nv_z, mini->plane->color);
	printf("sp-------------------\n%f,%f,%f  %f, %i\n", mini->sp->cx, mini->sp->cy, \
			mini->sp->cz, mini->sp->d, mini->sp->color);
	printf("cyl-------------------\n%f,%f,%f %f,%f,%f  %f  %f %i\n", mini->cyl->cx, mini->cyl->cy, mini->cyl->cz, \
			mini->cyl->nv_x, mini->cyl->nv_y, mini->cyl->nv_z, mini->cyl->d, mini->cyl->h, mini->cyl->color);
}

int	main(int argc, char **argv)
{
	t_mini	mini;

	if (argc == 2)
	{
		if (check_file(argv[1], &mini))
			return (1);
		init(&mini, argv);
		get_values(&mini);
		free_structs(&mini);
		if (!mini.is_valid)
			return (1);
	}
	else
		return (error_handler(1, 2));
	return (0);
}
