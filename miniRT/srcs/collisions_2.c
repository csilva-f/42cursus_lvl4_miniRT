/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:39:06 by csilva-f          #+#    #+#             */
/*   Updated: 2023/09/20 23:30:51 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	*cyl_collision_aux(t_cylinder *c, t_ray *r, t_vector *x)
{
	float	*d;

	d = malloc(sizeof(float) * 3);
	(*x) = vector_create(r->p0, c->pos);
	d[0] = vector_dot(r->v1, c->vec);
	d[2] = vector_dot((*x), c->vec);
	d[1] = vector_dot((*x), (*x)) - d[2] * d[2] - c->d_squared;
	d[1] = quadratic_form(r->sqrt_len - d[0] * d[0], \
		(vector_dot(r->v1, (*x)) - d[0] * d[2]) * 2, d[1]);
	return (d);
}

void	cyl_collision_aux2(t_cylinder *c, t_ray *r, float *d, t_vector x)
{
	r->t = d[1];
	r->reflex_times--;
	r->color = c->color;
	r->norm_v = vector_norm(vector_sub(vector_create(ray_pos(r->p0, r->v1, \
						d[1]), c->pos), vector_mult_const(c->vec, x.vx)));
}

bool	cylinder_collision(t_cylinder *c, t_ray *r)
{
	t_vector	x;
	float		*dx_v_ce;

	dx_v_ce = cyl_collision_aux(c, r, &x);
	if (dx_v_ce[1] > 0)
	{
		if (r->t == -1 || (dx_v_ce[1] < r->t))
		{
			x.vx = dx_v_ce[0] * dx_v_ce[1] + dx_v_ce[2];
			x.vy = distance(c->pos, ray_pos(c->pos, c->vec, c->h));
			if (x.vx > 0 && x.vx < x.vy)
			{
				cyl_collision_aux2(c, r, dx_v_ce, x);
				free(dx_v_ce);
				return (true);
			}
			else
			{
				free(dx_v_ce);
				return (bases(c, r, x.vx, 0));
			}
		}
	}
	free(dx_v_ce);
	return (true);
}

bool	plane_collision(t_plane *pl, t_ray *r1)
{
	float	denom;
	float	nom;
	float	t;

	denom = vector_dot(r1->v1, pl->vec);
	nom = vector_dot(vector_create(r1->p0, pl->pos), pl->vec);
	if ((denom < 0 && nom >= 0) || (denom > 0 && nom <= 0))
	{
		t = -1 * nom / denom;
		if (t > 0)
		{
			if (r1->t == -1 || (t < r1->t))
			{
				r1->t = t;
				r1->reflex_times--;
				r1->color = pl->color;
				if (denom < 0)
					r1->norm_v = vector_mult_const(pl->vec, -1);
				else
					r1->norm_v = pl->vec;
				return (true);
			}
		}
	}
	return (false);
}
