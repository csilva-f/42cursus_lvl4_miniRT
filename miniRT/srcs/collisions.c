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

float		quadratic_form(float a, float b, float c)
{
	float t_plus;
	float t_minus;

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

bool	cylinder_collision(t_cylinder *cyl, t_ray *r)
{
	t_vector	x;
	float		d_v;
	float		c;
	float		x_v;

	x = vector_create(r->p0, cyl->pos);
	d_v = vector_dot(r->v1, cyl->vec);
	x_v = vector_dot(x, cyl->vec);
	c = vector_dot(x, x) - x_v * x_v - cyl->d_squared;
	c = quadratic_form(r->sqrt_len - d_v * d_v,\
		(vector_dot(r->v1, x) - d_v * x_v) * 2, c);
	if (c > -1)
	{
		if (r->t == -1 || (c < r->t))
			{
				r->t = c;
				r->reflex_times--;
				r->color = cyl->color;
				return (true);
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
				return (true);
			}
		}
	}
	return (false);
}
