/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:42:57 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/29 16:42:59 by fvieira          ###   ########.fr       */
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
*/

//https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

float	quadratic_form(float a, float b, float c)
{
	float	t_plus;
	float	t_minus;

	t_plus = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a);
	t_minus = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a);
	//printf("t_minus %f t_plus %f\n", t_minus, t_plus);
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

bool	cylinder_collision(t_cylinder *c, t_ray *r)
{
	t_vector	x;
	float		m;
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
			m = d_v * ce + x_v;
			if (m < 0 || m > distance(c->pos,ray_pos(c->pos, c->vec, c->h)))
				return (false);
			r->t = ce;
			r->reflex_times--;
			r->color = c->color;
			return (true);
		}
	}
	return (true);
}

/*
bool	cylinder_collision(t_cylinder *c, t_ray *r)
{
	t_vector	x;
	t_vector	d;
	t_vector	temp;
	float		t;

	x = vector_sub(r->v1, vector_mult_const(c->vec, vector_dot(r->v1, c->vec)));
	temp = vector_create(r->p0, c->pos);
	d = vector_sub(temp, vector_mult_const(c->vec, vector_dot(temp, c->vec)));
	printf("antes\n");
	t = quadratic_form(vector_dot(x, x), 2 * vector_dot(x, d),\
		vector_dot(d, d) - c->d_squared);
	printf("depois\n");
	if (t > -1)
	{
		if (r->t == -1 || (t < r->t))
		{
			r->t = t;
			r->reflex_times--;
			r->color = c->color;
			return (true);
		}
	}
	return (true);
}
*/
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
	nom = vector_dot(vector_create(pl->pos, r1->p0), pl->vec);
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
				return (true);
			}
		}
	}
	return (false);
}
