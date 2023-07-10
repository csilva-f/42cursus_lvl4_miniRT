/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_camera_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:47:40 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/10 18:47:43 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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