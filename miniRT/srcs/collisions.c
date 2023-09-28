/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:42:57 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/24 18:10:17 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%2\
	  0dragan%20raytracing%20shapes.htm
*/

float	quadratic_form(float a, float b, float c)
{
	float	t_plus;
	float	t_minus;

	t_plus = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t_minus = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
	if (t_plus >= 0 && (t_minus <= 0 || t_plus <= t_minus))
		return (t_plus);
	else if (t_minus >= 0)
		return (t_minus);
	else
		return (-1);
}

bool	sphere_collision(t_sphere *sp, t_ray *r)
{
	t_vector	x;
	float		c;
	float		t;

	x = vector_create(r->p0, sp->pos);
	c = vector_dot(x, x) - sp->d_squared;
	t = quadratic_form(r->sqrt_len, vector_dot(r->v1, x) * 2, c);
	if (t > -1)
	{
		if (r->t == -1 || (t < r->t))
		{
			r->t = t;
			r->reflex_times--;
			r->color = sp->color;
			r->norm_v = vector_norm(vector_create(ray_pos(r->p0, \
							r->v1, t), sp->pos));
			return (true);
		}
	}
	return (false);
}

void	bases_aux(t_cylinder *c, float b, t_pos *p, t_vector *v)
{
	if (b >= 0.3)
	{
		(*p) = ray_pos(c->pos, c->vec, c->h / 2);
		(*v) = vector_mult_const(c->vec, -1);
	}
	else
	{
		(*v) = c->vec;
		(*p) = ray_pos(c->pos, vector_mult_const(c->vec, -1), c->h / 2);
	}
}

void	bases_aux_2(t_ray *r, t_vector v, float *n_d)
{
	if (n_d[1] < 0)
		r->norm_v = v;
	else
		r->norm_v = vector_mult_const(v, -1);
}

bool	bases(t_cylinder *c, t_ray *r, float base, float t)
{
	float		n_d[2];
	t_pos		pos;
	t_vector	vec;

	bases_aux(c, base, &pos, &vec);
	n_d[1] = vector_dot(r->v1, vec);
	n_d[0] = vector_dot(vector_create(r->p0, pos), vec);
	if ((n_d[1] < 0 && n_d[0] >= 0) || (n_d[1] > 0 && n_d[0] <= 0))
	{
		t = -1 * n_d[0] / n_d[1];
		if (t > 0)
		{
			if (r->t == -1 || (t < r->t))
			{
				float dist = distance(pos, ray_pos(r->p0, r->v1, t));
				printf(" distance %f  d %f\n", dist, c->d);
				if (dist >= c->d)
					return (false);
				r->t = t;
				r->reflex_times--;
				r->color = c->color;
				bases_aux_2(r, vec, n_d);
				return (true);
			}
		}
	}
	return (false);
}
