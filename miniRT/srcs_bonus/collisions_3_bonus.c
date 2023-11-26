/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:49:33 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/26 16:45:19 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

bool	plane_collision(t_plane *pl, t_ray *r, double t, double nom)
{
	double	denom;

	denom = vector_dot(r->v1, pl->vec);
	nom = vector_dot(vector_create(r->p0, pl->pos), pl->vec);
	if ((denom < 0 && nom >= 0) || (denom > 0 && nom <= 0))
	{
		t = -1 * nom / denom;
		if (t > 0)
		{
			if (r->t == -1 || (t < r->t))
			{
				plane_collision_aux(pl, &r, t);
				if (denom < 0)
					r->norm_v = pl->vec;
				else
					r->norm_v = vector_mult_const(pl->vec, -1);
				if (pl->checkboard == 1)
					r->color = color_condition(pl, ray_pos(r->p0, r->v1, t));
				return (true);
			}
		}
	}
	return (false);
}

double	quadratic_form_cone(double **a)
{
	double	t_plus;
	double	t_minu;
	double	aux;

	aux = sqrt((*a)[1] * (*a)[1] - 4 * (*a)[0] * (*a)[2]);
	t_plus = (-1 * (*a)[1] + aux) / (2 * (*a)[0]);
	aux = sqrt((*a)[1] * (*a)[1] - 4 * (*a)[0] * (*a)[2]);
	t_minu = (-1 * (*a)[1] - aux) / (2 * (*a)[0]);
	(*a)[5] = t_plus;
	(*a)[6] = t_minu;
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
		r->shine = c->shine;
		if (vector_dot(r->v1, c->vec) < 0)
			r->norm_v = c->vec;
		else
			r->norm_v = vector_mult_const(c->vec, -1);
		return (r->t);
	}
	return (-1);
}

void	cone_norm(t_cone *co, t_ray *r, double t, double m)
{
	t_vector	new;

	new = vector_create(ray_pos(r->p0, r->v1, t), co->pos);
	new = vector_sub(new, vector_mult_const(co->vec, pow(co->k, 2) * m));
	r->norm_v = vector_norm(new);
	r->reflex_times--;
	r->color = co->color;
	r->shine = co->shine;
	r->t = t;
}

void	cone_collision_aux(t_cone *co, t_ray *r, double **a, t_vector *x)
{
	double	aux;

	(*a) = malloc(7 * sizeof(double));
	(*x) = vector_create(r->p0, co->pos);
	(*a)[3] = vector_dot(r->v1, co->vec);
	(*a)[4] = vector_dot((*x), co->vec);
	(*a)[0] = r->sqrt_len - co->k_k * pow((*a)[3], 2);
	(*a)[1] = 2 * (vector_dot(r->v1, (*x)) - co->k_k * (*a)[3] * (*a)[4]);
	aux = pow(vector_dot((*x), co->vec), 2);
	(*a)[2] = vector_dot((*x), (*x)) - co->k_k * aux;
	(*a)[0] = quadratic_form_cone(a);
}
