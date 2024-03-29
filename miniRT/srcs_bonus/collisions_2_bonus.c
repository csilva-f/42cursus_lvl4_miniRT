/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:39:06 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/12 13:33:15 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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
	r->shine = c->shine;
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

t_pos	color_condition(t_plane *pl, t_pos p)
{
	double	a;
	double	b;

	a = 0;
	b = 0;
	if (pl->vec.vx != 0)
	{
		a = p.z;
		b = p.y;
	}
	else if (pl->vec.vy != 0)
	{
		a = p.x;
		b = p.z;
	}
	else if (pl->vec.vz != 0)
	{
		a = p.x;
		b = p.y;
	}
	if ((int)(floor(a) + floor(b)) % 2)
		return (pl->color);
	else
		return (pl->color2);
}

void	plane_collision_aux(t_plane *pl, t_ray **r, double t)
{
	(*r)->t = t;
	(*r)->reflex_times--;
	(*r)->color = pl->color;
	(*r)->shine = pl->shine;
}
