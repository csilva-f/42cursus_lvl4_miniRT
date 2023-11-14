/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:38:43 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/14 21:48:01 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	pl_new_aux(t_mini *m, char **vars, t_plane **pl)
{
	fill_colors(m, vars[3], &(*pl)->color);
	(*pl)->shine = ft_atoi(vars[4]);
	if (vars[5] != 0)
	{
		(*pl)->checkboard = 1;
		fill_colors(m, vars[5], &(*pl)->color2);
	}
}

t_plane	*pl_new(t_mini *m, char **vars, char ***data)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->pos.x = float_check(m, (*data)[0]);
	pl->pos.y = float_check(m, (*data)[1]);
	pl->pos.z = float_check(m, (*data)[2]);
	pl->checkboard = 0;
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		pl->vec.vx = float_check(m, (*data)[0]);
		pl->vec.vy = float_check(m, (*data)[1]);
		pl->vec.vz = float_check(m, (*data)[2]);
		if (fabs(pl->vec.vx) > 1 || fabs(pl->vec.vy) > 1
			|| fabs(pl->vec.vz) > 1 || length(pl->vec) != 1)
			vars_errors(m, 4);
		else
			pl_new_aux(m, vars, &pl);
	}
	pl->next = NULL;
	pl->coef = -1 * vector_dot(pl->vec, pos_to_vector(pl->pos));
	return (pl);
}

t_plane	*pl_last(t_plane *pl)
{
	t_plane	*aux;

	if (!pl)
		return (NULL);
	aux = pl;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	pl_add_b(t_plane **pl, t_plane *pl_new)
{
	t_plane	*aux;

	if (pl)
	{
		if (*pl)
		{
			aux = pl_last(*pl);
			aux->next = pl_new;
			pl_new = aux;
		}
		else
			*pl = pl_new;
	}
}

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}
