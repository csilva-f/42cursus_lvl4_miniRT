/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:28:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/07/11 00:45:20 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	sph_add_b(t_sphere **sp, t_sphere *sp_new)
{
	t_sphere	*aux;

	if (sp)
	{
		if (*sp)
		{
			aux = sph_last(*sp);
			aux->next = sp_new;
			sp_new = aux;
		}
		else
			*sp = sp_new;
	}
}

t_cylinder	*cy_new(t_mini *m, char **vars, char ***data)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->cx = float_check(m, (*data)[0]);
	cy->cy = float_check(m, (*data)[1]);
	cy->cz = float_check(m, (*data)[2]);
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		cy->nv_x = float_check(m, (*data)[0]);
		cy->nv_y = float_check(m, (*data)[1]);
		cy->nv_z = float_check(m, (*data)[2]);
		if (fabs(cy->nv_x) > 1 || fabs(cy->nv_y) > 1 || fabs(cy->nv_z) > 1)
			vars_errors(m, 4);
		else
		{
			cy->d = float_check(m, vars[3]);
			cy->h = float_check(m, vars[4]);
			cy->color = fill_colors(m, vars[5], -1);
		}
	}
	cy->next = NULL;
	return (cy);
}

t_cylinder	*cy_last(t_cylinder *cy)
{
	t_cylinder	*aux;

	if (!cy)
		return (NULL);
	aux = cy;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	cy_add_b(t_cylinder **cy, t_cylinder *cy_new)
{
	t_cylinder	*aux;

	if (cy)
	{
		if (*cy)
		{
			aux = cy_last(*cy);
			aux->next = cy_new;
			cy_new = aux;
		}
		else
			*cy = cy_new;
	}
}
