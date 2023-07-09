/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:00 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/09 15:54:44 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init(t_mini *mini, char **argv)
{
	mini->file = argv[1];
	mini->is_valid = 1;
	mini->al = malloc(sizeof(t_al));
	mini->cam = malloc(sizeof(t_cam));
}

void	check_identifier(t_mini *mini, char *str)
{
	if (!ft_strncmp(str, "A", 2) || !ft_strncmp(str, "C", 2) \
			|| !ft_strncmp(str, "L", 2) || !ft_strncmp(str, "pl", 3) \
			|| !ft_strncmp(str, "sp", 3) || !ft_strncmp(str, "cy", 3))
		mini->is_valid = 1;
	else
		mini->is_valid = 0;
}

int rgb_to_int(int red, int green, int blue)
{
    int	res;

	res = (red * 65536) + (green * 256) + blue;
    return (res);
}

void	vars_errors(t_mini *mini, int code)
{
	mini->is_valid = 0;
	error_handler(code);	
}

int	count_vars(char **vars, int equal, int code, t_mini *m)
{
	int	i;

	i = 0;
	while (vars[i] != 0 && ft_strncmp(vars[i], "\0", 1))
		i++;
	if (i == equal)
		return (1);
	else
	{
		vars_errors(m, code);
		return (0);
	}
}

int	fill_colors(t_mini *m, char **color)
{
	int	c;
	int	r;
	int	g;
	int	b;

	c = -1;
	ft_remove_lb(color[2]);
	if (ft_str_isdigit(color[0]) && ft_str_isdigit(color[1]) \
			&& ft_str_isdigit(color[2]))
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
	return (c);;
}

float float_check(t_mini *m, char *str)
{
	float	nbr;
	char	**parts;

	nbr = -1;
	parts = ft_split(str, '.');
	if (count_vars(parts, 2, 4, m))
	{
		if (ft_str_isdigit(parts[0]) && ft_str_isdigit(parts[1]))
			nbr = ft_atoi(parts[0]) + (float)ft_atoi(parts[1])
			/ powf(10, ft_strlen(parts[1]));
		else
			vars_errors(m, 4);
	}
	ft_free_split(&parts);
	return (nbr);
}

int	check_A_vars(t_mini *m, char **vars)
{
	char	**color;

	m->al->ratio = float_check(m, vars[1]);
	if (m->is_valid)
	{
		color = ft_split(vars[2], ',');
		if (count_vars(color, 3, 4, m))
		{
			m->al->color = fill_colors(m, color);
			ft_free_split(&color);
		}
	}
	else
		return (1);
	return (0);
}

void	check_C_vars(t_mini *m, char **vars)
{
	char	**coords;
	char	**o_vector;

	coords = ft_split(vars[1], ',');
	if (count_vars(coords, 3, 4, m))
	{
		m->cam->x = float_check(m, coords[0]);
		m->cam->y = float_check(m, coords[1]);
		m->cam->z = float_check(m, coords[2]);
		ft_free_split(&coords);
		o_vector = ft_split(vars[2], ',');
		if (count_vars(o_vector, 3, 4, m))
		{
			m->cam->ov_x = float_check(m, o_vector[0]);
			m->cam->ov_y = float_check(m, o_vector[1]);
			m->cam->ov_z = float_check(m, o_vector[2]);
			if (fabsf(m->cam->ov_x) > 1 || fabsf(m->cam->ov_y) > 1 \
					|| fabsf(m->cam->ov_y) > 1)
				vars_errors(m, 4);
			ft_free_split(&o_vector);
			if (ft_str_isdigit(vars[3]))
			{
				m->cam->fov = ft_atoi(vars[3]);
				if (m->cam->fov > 180 || m->cam->fov < 0)
					vars_errors(m, 4);
			}
			else
				vars_errors(m, 4);
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
		ft_free_split(&data);
		data = ft_split(vars[2], ',');
		if (count_vars(data, 3, 4, m))
		{
			m->plane->nv_x = float_check(m, data[0]);
			m->plane->nv_y = float_check(m, data[1]);
			m->plane->nv_z = float_check(m, data[2]);
			ft_free_split(&data);
			data = ft_split(vars[3], ',');
			if (fabs(m->plane->nv_x) > 1 || fabs(m->plane->nv_y) > 1 \
				|| fabs(m->plane->nv_z) > 1)
				vars_errors(m, 4);
			else
				m->plane->color = fill_colors(m, data);
			ft_free_split(&data);
		}
	}
}

void	check_line_values(t_mini *mini, char **vars)//, int i)
{
	int		i;

	i = 0;
	if (!ft_strncmp(vars[0], "A", 2))
	{
		if (count_vars(vars, 3, 5, mini))
			check_A_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "C", 2))
	{
		if (count_vars(vars, 4, 5, mini))
			check_C_vars(mini, vars);
	}
	else if (!ft_strncmp(vars[0], "L", 2))
	{
		if (count_vars(vars, 4, 5, mini))
			check_L_vars(mini, vars);
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

int	check_lines(t_mini *mini, char *aux)
{
	int	len_id;
	char **vars;

	vars = ft_split(aux, ' ');
	check_identifier(mini, vars[0]);
	if (!mini->is_valid)
		return (error_handler(3));
	check_line_values(mini, vars);
	return (0);
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
		
	}
}

int	main(int argc, char **argv)
{
	t_mini	mini;

	if (argc == 2)
	{
		if (check_file(argv[1], &mini))
			return (1);
	}
	else
		return(error_handler(2));
	return (0);
}
