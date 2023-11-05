/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:44:00 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/11 00:21:53 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	check_pl_vars(t_mini *m, char **vars)
{
	char	**data;
	t_plane	*pl;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
	{
		pl = pl_new(m, vars, &data);
		pl_add_b(&m->plane, pl);
	}
	ft_free_split(data);
}

void	check_sp_vars(t_mini *m, char **vars)
{
	char	**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
		sph_add_b(&m->sp, sph_new(m, vars, &data));
	ft_free_split(data);
}

void	check_cy_vars(t_mini *m, char **vars)
{
	char		**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
		cy_add_b(&m->cyl, cy_new(m, vars, &data));
	ft_free_split(data);
}

void	check_co_vars(t_mini *m, char **vars)
{
	char		**data;

	data = ft_split(vars[1], ',');
	if (count_vars(data, 3, 4, m))
		co_add_b(&m->co, co_new(m, vars, &data));
	ft_free_split(data);
}
