/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:17:36 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/11 00:44:52 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_plane	*pl_new(t_mini *m, char **vars, char ***data)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->x = float_check(m, (*data)[0]);
	pl->y = float_check(m, (*data)[1]);
	pl->z = float_check(m, (*data)[2]);
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		pl->nv_x = float_check(m, (*data)[0]);
		pl->nv_y = float_check(m, (*data)[1]);
		pl->nv_z = float_check(m, (*data)[2]);
		if (fabs(pl->nv_x) > 1 || fabs(pl->nv_y) > 1 || fabs(pl->nv_z) > 1)
			vars_errors(m, 4);
		else
			pl->color = fill_colors(m, vars[3], -1);
	}
	pl->next = NULL;
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

t_sphere	*sph_new(t_mini *m, char **vars, char ***data)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->cx = float_check(m, (*data)[0]);
	sp->cy = float_check(m, (*data)[1]);
	sp->cz = float_check(m, (*data)[2]);
	sp->d = float_check(m, vars[2]);
	sp->color = fill_colors(m, vars[3], -1);
	sp->next = NULL;
	return (sp);
}

t_sphere	*sph_last(t_sphere *sp)
{
	t_sphere	*aux;

	if (!sp)
		return (NULL);
	aux = sp;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}
