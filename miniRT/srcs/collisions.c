/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:42:57 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/16 16:35:36 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
typedef struct s_ray
{
	t_pos			p0;
	t_vector		v1;
	t_vector		norm_v;
	float			sqrt_len;
	float			t;
	int				reflex_times;
	int				color;
	struct t_ray	*next;
	struct t_ray	*prev;
}		t_ray;


https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/

//printf("t_minus %f t_plus %f\n", t_minus, t_plus);

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

/*
typedef struct s_sphere
{
	t_pos			pos;
	float			d;
	float			d_squared;
	int				color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;
*/

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
			r->norm_v = vector_norm(vector_create(ray_pos(r->p0, r->v1, t), sp->pos));
			return (true);
		}
	}
	return (false);
}

/*
typedef struct s_cylinder
{
	t_pos				pos;
	t_vector			vec;
	float				d;
	float				d_squared;
	float				h;
	int					color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}		t_cylinder;
*/

bool	bases(t_cylinder *c, t_ray *r, float base)
{
	float		denom;
	float		nom;
	float		t;
	t_pos		pos;
	t_vector	vec;

	if (base >= 0.3)
	{
		pos = ray_pos(c->pos, c->vec, c->h);
		vec = vector_mult_const(c->vec, -1);
	}
	else
	{
		vec = c->vec;
		pos = c->pos;
	}
	denom = vector_dot(r->v1, vec);
	nom = vector_dot(vector_create(r->p0, pos), vec);
	if ((denom < 0 && nom >= 0) || (denom > 0 && nom <= 0))
	{
		t = -1 * nom / denom;
		if (t > 0)
		{
			if (r->t == -1 || (t < r->t))
			{
				if (distance(pos, ray_pos(r->p0, r->v1, t)) > c->d)
					return (false);
				r->t = t;
				r->reflex_times--;
				r->color = c->color;
				if (denom < 0)
					r->norm_v = vector_mult_const(vec, -1);
				else
					r->norm_v = vec;
				return (true);
			}
		}
	}
	return (false);
}

bool	cylinder_collision(t_cylinder *c, t_ray *r)
{
	t_vector	x;
	float		d_v;
	float		ce;
	float		x_v;

	x = vector_create(r->p0, c->pos);
	d_v = vector_dot(r->v1, c->vec);
	x_v = vector_dot(x, c->vec);
	ce = vector_dot(x, x) - x_v * x_v - c->d_squared;
	ce = quadratic_form(r->sqrt_len - d_v * d_v, \
		(vector_dot(r->v1, x) - d_v * x_v) * 2, ce);
	if (ce > 0)
	{
		if (r->t == -1 || (ce < r->t))
		{
			x.vx = d_v * ce + x_v;
			x.vy = distance(c->pos,ray_pos(c->pos, c->vec, c->h));
			if (x.vx > 0 && x.vx < x.vy)
			{
				r->t = ce;
				r->reflex_times--;
				r->color = c->color;
				r->norm_v = vector_norm(vector_sub(vector_create(ray_pos(r->p0,\
					r->v1, ce), c->pos), vector_mult_const(c->vec, x.vx)));
				return (true);

			}
			else
				return (bases(c, r, x.vx));
		}
	}
	return (true);
}

/*
typedef struct s_plane
{
	t_pos			pos;
	t_vector		vec;
	float			coef;
	int				color;
	struct s_plane	*next;
	struct s_plane	*prev;
}		t_plane;
*/

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
