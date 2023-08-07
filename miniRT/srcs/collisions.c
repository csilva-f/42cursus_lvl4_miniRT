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

/*bool	sphere_collision(t_sphere *sp, t_ray *r1)
{
	float	xpart;
	float	ypart;
	float	zpart;
	float	tol;

	tol = 0.5;
	//definir aqui uma tolerancia decente pq calculos computacionais
	//trazem sempre incerteza e nao podem ser comparados com "=="
	xpart = (r1->p0.x - sp->pos.x) * (r1->p0.x - sp->pos.x);
	ypart = (r1->p0.y - sp->pos.y) * (r1->p0.y - sp->pos.y);
	zpart = (r1->p0.z - sp->pos.z) * (r1->p0.z - sp->pos.z);
	if (fabs(xpart + ypart + zpart - sp->d * sp->d) <= tol)
	{
		r1->norm_v = vector_norm(vector_create(r1->p0, sp->pos));
		r1->reflex_times--;
		return (true);
	}
	else
		return (false);
}*/

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
		r->t = t;
		r->reflex_times--;
		return (true);
	}
	return (false);
}

/*
bool	loop(t_cylinder *c, t_ray *r, t_vector c_vec)
{
	t_pos		p;
	t_vector	v1;
	t_vector	v2;
	float		t;

	t = 0;
	p = c->pos;
	while (distance(p, c->pos) <= c->h / 2)
	{
		t += 0.1; //tb vai ser preciso cuidado quanto aumentar t de cada vez
		p = ray_pos(c->pos, c_vec, t);
		v1 = vector_create(r->p0, p);
		v2 = vector_create(p, c->pos);
		//tol = 0.5, probably too big
		if (vector_dot(v1, v2) == 0 && (fabs(distance(r->p0, p) - c->d) <= 0.5
				|| (distance(p, c->pos) == c->h / 2 && distance(r->p0, p) <= c->d)))
		{
			r->norm_v = vector_norm(v2);
			r->reflex_times--;
			// norma para as bases dos cilindros nao 'e esta, vai ser como se fosse um plano
			return (true);
		}
	}
	return (false);
}

bool	cylinder_collision(t_cylinder *cyl, t_ray *r)
{
	t_vector	v1;

	v1 = vector_create(r->p0, cyl->pos);
	if (vector_dot(v1, cyl->vec) > 0)
		return (loop(cyl, r, cyl->vec));
	else
		return (loop(cyl, r, vector_mult_const(cyl->vec, -1)));
}
*/

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
		r->t = c;
		r->reflex_times--;
		return (true);
	}
	return (false);
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

// eq se ponto esta no plano 
// pl.vx * p1.x + pl.vy * p1.y + pl.vz * p1.z - pl->coef = 0

/*bool	plane_collision(t_plane *pl, t_ray *r1)
{
	float	tol;

	tol = 0.5; //define good tolerance
	if (fabs(vector_dot(pl->vec, pos_to_vector(r1->p0)) + pl->coef) <= tol)
	{
		r1->norm_v = vector_norm(pl->vec);
		r1->reflex_times--;
		return (true);
	}
	else
		return (false);
}
*/
//func anterior arcaica mas pode ter coisas aproveitaveis, agora vou seguir
// formula para descobrir ponte de intersecao t = -X|V / D|V

bool	plane_collision(t_plane *pl, t_ray *r1)
{
	float	denom;
	float	nom;

	denom = vector_dot(r1->v1, pl->vec);
	nom = vector_dot(vector_create(r1->p0, pl->pos), pl->vec);
	if ((denom < 0 && nom >= 0) || (denom > 0 && nom <= 0))
	{
		r1->t = -1 * nom / denom;
		r1->reflex_times--;
		return (true);
	}
	else
		return (false);
}

	//depois verificar de que lado do plano se esta para ficar com o vetor normal
	//correto