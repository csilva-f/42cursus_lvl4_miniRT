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
typedef struct s_sphere
{
	t_pos			pos;
	float			d;
	int				color;
	struct s_sphere	*next;
	struct s_sphere	*prev;
}		t_sphere;
*/

bool	sphere_collision(t_sphere *sp, t_pos p1)
{
	float	xpart;
	float	ypart;
	float	zpart;
	float	tol;

	tol = 0.5;
	//definir aqui uma tolerancia decente pq calculos computacionais
	//trazem sempre incerteza e nao podem ser comparados com "=="
	xpart = (p1.x - sp->pos.x) * (p1.x - sp->pos.x);
	ypart = (p1.y - sp->pos.y) * (p1.y - sp->pos.y);
	zpart = (p1.z - sp->pos.z) * (p1.z - sp->pos.z);
	if (fabs(xpart + ypart + zpart - sp->d * sp->d) <= tol)
		return (true);
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

bool	loop(t_cylinder *cyl, t_pos p1, t_vector cyl_vec)
{
	t_pos		p2;
	t_vector	v1;
	t_vector	v2;
	float		t;

	t = 0;
	p2 = cyl->pos;
	while (distance(p2, cyl->pos) < cyl->h / 2)
	{
		t += 0.1; //tb vai ser preciso cuidado quanto aumentar t de cada vez
		p2 = ray_pos(cyl->pos, cyl_vec, t);
		v1 = vector_create(p1, p2);
		v2 = vector_create(p2, cyl->pos);
		//tol=0.5, probably too big
		if (vector_dot(v1, v2) == 0 && fabs(distance(p1, p2) - cyl->d) <= 0.5)
			return (true);
	}
	if (distance(p2, cyl->pos) == cyl->h / 2)
		if (vector_dot(v1, v2) == 0 && distance(p1, p2) <= cyl->d)
			return (true);
	return (false);
}

bool	cylinder_collision(t_cylinder *cyl, t_pos p1)
{
	t_vector	v1;

	v1 = vector_create(p1, cyl->pos);
	if (vector_dot(v1, cyl->vec) > 0)
		return (loop(cyl, p1, cyl->vec));
	else
		return (loop(cyl, p1, vector_mult_const(cyl->vec, -1)));
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

bool	plane_collision(t_plane *pl, t_pos p1)
{
	float	tol;

	tol = 0.5; //define good tolerance
	if (fabs(vector_dot(pl->vec, pos_to_vector(p1)) + pl->coef) <= tol)
		return (true);
	else
		return (false);
}

t_vector	plane_norm(t_plane *pl, t_pos p1)
{

}