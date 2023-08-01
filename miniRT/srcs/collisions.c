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
	int				reflex_times;
	struct t_ray	*next;
	struct t_ray	*prev;
}		t_ray;
*/

/*
typedef struct s_sphere
{
	t_pos			pos;
	float			d;
	int				color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;
*/

bool	sphere_collision(t_sphere *sp, t_ray *r1)
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
		r1->norm_v = vector_create(r1->p0, sp->pos);
		r1->reflex_times--;
		return (true);
	}
	else
		return (false);
}

/*
typedef struct s_cylinder
{
	t_pos				pos;
	t_vector			vec;
	float				d;
	float				h;
	int					color;
	struct s_cylinder	*next;
	struct s_cylinder	*prev;
}		t_cylinder;
*/

// logica vai ser que para cada ponto p1 no percurso do raio encontrar o ponto
// p2 que esteja na linha (infinita) do centro do cyl que unindo com p1 crie
// um vetor perpendicular ao vetor que une p2 ao centro do cyl O ou seja
// p1p2 . Op2 = 0 e depois ver se p2 esta dentro da altura do cilindro e se p1
// esta a distancia d do cilindro para as paredes ou <= d se estiver nas bases

//primeiro vou fazer o dot de p1 com a O para ver se o ponto esta a cima
// ou abaixo para eliminar logo metade dos calculos

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
		//tol=0.5, probably too big
		if (vector_dot(v1, v2) == 0 && (fabs(distance(r->p0, p) - c->d) <= 0.5
			|| (distance(p, c->pos) == c->h / 2 && distance(r->p0, p) <= c->d)))
		{
			r->norm_v = v2;
			r->reflex_times--;
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

bool	plane_collision(t_plane *pl, t_ray *r1)
{
	float	tol;

	tol = 0.5; //define good tolerance
	if (fabs(vector_dot(pl->vec, pos_to_vector(r1->p0)) + pl->coef) <= tol)
	{
		r1->norm_v = pl->vec;
		r1->reflex_times--;
		return (true);
	}
	else
		return (false);
}
