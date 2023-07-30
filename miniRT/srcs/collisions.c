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

bool	sphere_colision(t_sphere *sp, t_pos p1)
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
// p2 que esteja na linha (infinita) do centro do cilindro que unindo com p1 crie
// um vetor perpendicular ao vetor que une p2 ao centro do cilindro O que corresponde a eq
// p1p2 . Op2 = 0 e depois ver se p2 esta dentro da altura do cilindro e se p1
// esta a distancia d do cilindro para as paredes ou <= d se estiver nas bases

//primeiro vou fazer o dot de p1 com a O para ver se o ponto esta a cima
// ou abaixo para eliminar logo metade dos calculos
bool	cylinder_colision(t_cylinder *cyl, t_pos p1)
{
	t_pos		p2;
	t_vector	v1;
	t_vector	v2;
	float		t;

	v1 = vector_create(p1, cyl->pos);
	if (vector_dot(v1, cyl->vec) > 0)
	{
		t = 0;
		p2 = cyl->pos;
		while (distance(p2, cyl->pos) < cyl->h / 2)
		{
			t += 0.1; //tb vai ser preciso cuidado quanto aumentar t de cada vez
			p2 = ray_pos(cyl->pos, cyl->vec, t);
			v1 = vector_create(p1, p2);
			v2 = vector_create(p2, cyl->pos);
			//tol=0.5, probably too big
			if (vector_dot(v1, v2) == 0 && fabs(distance(p1, p2) - cyl->d) <= 0.5)
				return (true);
		}
		if (distance(p2, cyl->pos) == cyl->h / 2)
			if (vector_dot(v1, v2) == 0 && distance(p1, p2) <= cyl->d)
				return (true);
	}
	else
	{
		t = 0;
		p2 = cyl->pos;
		while (distance(p2, cyl->pos) < cyl->h / 2)
		{
			t += 0.1; //tb vai ser preciso cuidado quanto aumentar t de cada vez
			p2 = ray_pos(cyl->pos, vector_mult_const(cyl->vec, -1), t);
			v1 = vector_create(p1, p2);
			v2 = vector_create(p2, cyl->pos);
			//tol=0.5, probably too big
			if (vector_dot(v1, v2) == 0 && fabs(distance(p1, p2) - cyl->d) <= 0.5)
				return (true);
		}
		if (distance(p2, cyl->pos) == cyl->h / 2)
			if (vector_dot(v1, v2) == 0 && distance(p1, p2) <= cyl->d)
				return (true);
	}
	return (false);
}
