/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:49:33 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/07 23:03:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

// co -> pos vec k(degrees) h color

void	cone_norm(t_cone *co, t_ray *r, double t, double m)
{
	t_vector	new;

	new = vector_create(ray_pos(r->p0, r->v1, t), co->pos);
	new = vector_sub(new, vector_mult_const(co->vec, pow(co->k, 2) * m));
	r->norm_v = vector_norm(new);
	r->reflex_times--;
	r->color = co->color;
	r->t = t;
}

double	quadratic_form_cone(double a, double b, double c, double *t)
{
	double	t_plus;
	double	t_minu;

	t_plus = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t_minu = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
	t[0] = t_plus;
	t[1] = t_minu;
	if (t_plus >= 0 && (t_minu <= 0 || t_plus <= t_minu))
		return (t_plus);
	else if (t_minu >= 0)
		return (t_minu);
	else
		return (-1);
}

double	cone_bases(t_cone *c, t_ray *r, double t)
{
	double		n[2];
	t_pos		pos;

	pos = ray_pos(c->pos, c->vec, c->h);
	n[1] = vector_dot(r->v1, c->vec);
	n[0] = vector_dot(vector_create(r->p0, pos), c->vec);
	if (n[1] == 0)
		return (-1);
	t = -1 * n[0] / n[1];
	if (t > 0 && (r->t == -1 || (t < r->t)))
	{
		if (distance(pos, ray_pos(r->p0, r->v1, t)) >= c->k * c->h)
			return (-1);
		r->t = t;
		r->reflex_times--;
		r->color = c->color;
		if (vector_dot(r->v1, c->vec) < 0)
			r->norm_v = c->vec;
		else
			r->norm_v = vector_mult_const(c->vec, -1);
		return (r->t);
	}
	return (-1);
}

bool	cone_collision(t_cone *co, t_ray *r)
{
	double		a;
	double		b;
	double		c;
	double		d_v;
	double		x_v;
	double		t[2];
	t_vector	x;

	x = vector_create(r->p0, co->pos);
	d_v = vector_dot(r->v1, co->vec);
	x_v = vector_dot(x, co->vec);
	a = r->sqrt_len - co->k_k * pow(d_v, 2);
	b = 2 * (vector_dot(r->v1, x) - co->k_k * d_v * x_v);
	c = vector_dot(x, x) - co->k_k * pow(vector_dot(x, co->vec), 2);
	a = quadratic_form_cone(a, b, c, t);
	if (a > 0.05)
	{
		if (vector_dot(vector_create(ray_pos(r->p0, r->v1, a), co->pos), \
					co->vec) < 0)
		{
			if (a == t[0])
				a = t[1];
			else if (a == t[1])
				a = t[0];
			if (a < 0.05 || vector_dot(vector_create(ray_pos(r->p0, r->v1, a), \
							co->pos), co->vec) < 0)
				return (false);
		}
		if (r->t == -1 || (a < r->t))
		{
			c = d_v * a + x_v;
			b = distance(co->pos, ray_pos(co->pos, co->vec, co->h));
			if (c <= b)
			{
				r->t = cone_bases(co, r, 0);
				if (a < r->t || r->t <= 0)
					cone_norm(co, r, b, c);
				return (true);
			}
			else if (c > b)
				return (cone_bases(co, r, 0));
		}
	}
	return (false);
}
