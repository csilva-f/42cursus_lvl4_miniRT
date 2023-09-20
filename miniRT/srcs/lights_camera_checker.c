/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_camera_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:47:40 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/20 21:56:54 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	check_a_vars(t_mini *m, char **vars)
{
	m->counter_a++;
	if (m->counter_a > 1)
	{
		vars_errors(m, 7);
		return ;
	}
	m->al->ratio = float_check(m, vars[1]);
	if (m->is_valid)
		fill_colors(m, vars[2], &m->al->color);
}

int	counter_c(t_mini *m)
{
	m->counter_c++;
	if (m->counter_c > 1)
		vars_errors(m, 7);
	return (m->counter_c);
}

void	check_c_vars(t_mini *m, char **v, char **data)
{
	if (counter_c(m) > 1)
		return ;
	data = ft_split(v[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->cam->pos.x = float_check(m, data[0]);
		m->cam->pos.y = float_check(m, data[1]);
		m->cam->pos.z = float_check(m, data[2]);
		ft_free_split(data);
		data = ft_split(v[2], ',');
		if (count_vars(data, 3, 4, m))
		{
			m->cam->vec.vx = float_check(m, data[0]);
			m->cam->vec.vy = float_check(m, data[1]);
			m->cam->vec.vz = float_check(m, data[2]);
			if (fabsf(m->cam->vec.vx) > 1 || fabsf(m->cam->vec.vy) > 1 \
					|| fabsf(m->cam->vec.vz) > 1)
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
	char		**data;

	m->counter_l++;
	if (m->counter_l > 1)
	{
		vars_errors(m, 7);
		return ;
	}
	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		m->light->pos.x = float_check(m, data[0]);
		m->light->pos.y = float_check(m, data[1]);
		m->light->pos.z = float_check(m, data[2]);
		ft_free_split(data);
		if (m->is_valid)
		{
			m->light->ratio = float_check(m, vars[2]);
			if (m->light->ratio < 0 || m->light->ratio > 1)
				vars_errors(m, 4);
			else
				fill_colors(m, vars[3], &m->light->color);
		}
	}
}
