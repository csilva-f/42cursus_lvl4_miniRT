/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_4_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:44:50 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/26 17:07:46 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

bool	cone_collisions_aux2(double **a, t_cone *co, t_ray *r)
{
	(*a)[2] = (*a)[3] * (*a)[0] + (*a)[4];
	(*a)[1] = distance(co->pos, ray_pos(co->pos, co->vec, co->h));
	if ((*a)[2] < (*a)[1])
	{
		r->t = cone_bases(co, r, 0);
		if ((*a)[0] < r->t || r->t < 0)
			cone_norm(co, r, (*a)[0], (*a)[2]);
		free((*a));
		return (true);
	}
	else if ((*a)[2] >= (*a)[1])
	{
		free((*a));
		return (cone_bases(co, r, 0));
	}
	return (false);
}

bool	cone_collision(t_cone *co, t_ray *r, double *a, t_vector x)
{
	t_vector	aux;

	cone_collision_aux(co, r, &a, &x);
	if (a[0] > 0.05)
	{
		if (vector_dot(vector_create(ray_pos(r->p0, r->v1, a[0]), co->pos), \
					co->vec) < 0)
		{
			if (a[0] == a[5])
				a[0] = a[6];
			else if (a[0] == a[6])
				a[0] = a[5];
			aux = vector_create(ray_pos(r->p0, r->v1, a[0]), co->pos);
			if (a[0] < 0.05 || vector_dot(aux, co->vec) < 0)
			{
				free(a);
				return (false);
			}
		}
		if (r->t == -1 || (a[0] < r->t))
			return (cone_collisions_aux2(&a, co, r));
	}
	free(a);
	return (false);
}
