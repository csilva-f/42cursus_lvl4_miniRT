/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:44:00 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/10 18:44:03 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

void	check_cy_vars(t_mini *m, char **vars, char **data)
{
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
