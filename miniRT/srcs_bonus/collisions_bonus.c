/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:42:57 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/14 22:07:46 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

/*
https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%
20dragan%20raytracing%20shapes.htm
*/

double	quadratic_form(double a, double b, double c)
{
	double	t_plus;
	double	t_minu;

	t_plus = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t_minu = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
	if (t_plus >= 0 && (t_minu <= 0 || t_plus <= t_minu))
		return (t_plus);
	else if (t_minu >= 0)
		return (t_minu);
	else
		return (-1);
}

bool	sphere_collision(t_sphere *sp, t_ray *r)
{
	t_vector	x;
	double		c;
	double		t;

	x = vector_create(r->p0, sp->pos);
	c = vector_dot(x, x) - sp->d_squared;
	t = quadratic_form(r->sqrt_len, vector_dot(r->v1, x) * 2, c);
	if (t > 0.005)
	{
		if (r->t == -1 || (t < r->t))
		{
			r->t = t;
			r->reflex_times--;
			r->color = sp->color;
			r->shine = sp->shine;
			r->norm_v = vector_norm(vector_create(ray_pos(r->p0, \
							r->v1, t), sp->pos));
			return (true);
		}
	}
	return (false);
}

/*if (r->t > 0)
			printf("t antes %f, t da esfera %f\n", r->t, t);*/

void	bases_aux_2(t_ray *r, t_vector v)
{
	if (vector_dot(r->v1, v) < 0)
		r->norm_v = v;
	else
		r->norm_v = vector_mult_const(v, -1);
}

double	bases_aux(double *n, t_pos *pos, t_vector *vec, t_cylinder *c)
{
	double	t[3];

	if (n[1] == 0)
		t[1] = -1;
	else
		t[1] = -1 * n[0] / n[1];
	if (n[3] == 0)
		t[2] = -1;
	else
		t[2] = -1 * n[2] / n[3];
	if (t[1] > 0 && (t[2] < 0 || t[1] < t[2]))
	{
		(*pos) = ray_pos(c->pos, vector_mult_const(c->vec, -1), c->h / 2);
		(*vec) = c->vec;
		t[0] = t[1];
	}
	else if (t[2] > 0)
	{
		(*pos) = ray_pos(c->pos, c->vec, c->h / 2);
		(*vec) = vector_mult_const(c->vec, -1);
		t[0] = t[2];
	}
	else
		t[0] = -1;
	return (t[0]);
}

double	bases(t_cylinder *c, t_ray *r, double t)
{
	double		n[4];
	t_pos		pos;
	t_vector	vec;

	n[1] = vector_dot(r->v1, c->vec);
	n[0] = vector_dot(vector_create(r->p0, ray_pos(c->pos, \
		vector_mult_const(c->vec, -1), c->h / 2)), c->vec);
	n[3] = vector_dot(r->v1, vector_mult_const(c->vec, -1));
	n[2] = vector_dot(vector_create(r->p0, ray_pos(c->pos, c->vec, c->h / 2)), \
		vector_mult_const(c->vec, -1));
	t = bases_aux(n, &pos, &vec, c);
	if (t > 0 && (r->t == -1 || (t < r->t)))
	{
		if (distance(pos, ray_pos(r->p0, r->v1, t)) >= c->d)
			return (-1);
		r->t = t;
		r->reflex_times--;
		r->color = c->color;
		r->shine = c->shine;
		bases_aux_2(r, vec);
		return (r->t);
	}
	return (-1);
}
