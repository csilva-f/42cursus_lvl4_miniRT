/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:39:06 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/28 16:30:41 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	cyl_collision_aux(double *d, t_cylinder *c, t_ray *r, t_vector *x)
{
	(*x) = vector_create(r->p0, c->pos);
	d[0] = vector_dot(r->v1, c->vec);
	d[2] = vector_dot((*x), c->vec);
	d[1] = vector_dot((*x), (*x)) - d[2] * d[2] - c->d_squared;
	d[1] = quadratic_form(r->sqrt_len - d[0] * d[0], \
		(vector_dot(r->v1, (*x)) - d[0] * d[2]) * 2, d[1]);
}

void	cyl_collision_aux2(t_cylinder *c, t_ray *r, double *d, t_vector x)
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
	double		dx_v_ce[3];

	cyl_collision_aux(dx_v_ce, c, r, &x);
	if (dx_v_ce[1] > 0)
	{
		if (r->t == -1 || (dx_v_ce[1] < r->t))
		{
			x.vx = dx_v_ce[0] * dx_v_ce[1] + dx_v_ce[2];
			x.vy = distance(c->pos, ray_pos(c->pos, c->vec, c->h));
			if (x.vx >= -1 * x.vy / 2 && x.vx <= x.vy / 2)
			{
				r->t = bases(c, r, 0);
				if (dx_v_ce[1] < r->t || r->t <= 0)
					cyl_collision_aux2(c, r, dx_v_ce, x);
				return (true);
			}
			else
				return (bases(c, r, 0));
		}
	}
	return (false);
}
//x.vy = distance(ray_pos(c->pos, vector_mult_const(c->vec, -1),
//c->h / 2), ray_pos(c->pos, c->vec, c->h / 2));*/

bool	plane_collision(t_plane *pl, t_ray *r1)
{
	double	denom;
	double	nom;
	double	t;

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
					r1->norm_v = pl->vec;
				else
					r1->norm_v = vector_mult_const(pl->vec, -1);
				return (true);
			}
		}
	}
	return (false);
}
