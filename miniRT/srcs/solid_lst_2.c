/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_lst_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:28:07 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/19 22:15:54 by csilva-f         ###   ########.fr       */
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

void	cy_new_aux(t_mini *m, char ***data, t_cylinder **c)
{
	(*c)->pos = coord_new(float_check(m, (*data)[0]), float_check(m, \
				(*data)[1]), float_check(m, (*data)[2]));
}

t_cylinder	*cy_new(t_mini *m, char **vars, char ***data)
{
	t_cylinder	*c;

	c = malloc(sizeof(t_cylinder));
	cy_new_aux(m, data, &c);
	ft_free_split(*data);
	*data = ft_split(vars[2], ',');
	if (count_vars(*data, 3, 4, m))
	{
		c->vec = vector_new(float_check(m, (*data)[0]), float_check(m, \
					(*data)[1]), float_check(m, (*data)[2]));
		if (fabs(c->vec.vx) > 1 || fabs(c->vec.vy) > 1 || fabs(c->vec.vz) > 1
			|| length(c->vec) != (float) 1)
			vars_errors(m, 4);
		else
		{
			c->d = float_check(m, vars[3]) / 2;
			c->d_squared = c->d * c->d;
			c->h = float_check(m, vars[4]);
			fill_colors(m, vars[5], &c->color);
			c->pos = ray_pos(c->pos, c->vec, c->h / 2);
			c->vec = vector_mult_const(c->vec, -1);
		}
	}
	c->next = NULL;
	return (c);
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
