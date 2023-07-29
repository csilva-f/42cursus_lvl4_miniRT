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
	float xpart;
	float ypart;
	float zpart;
	float tol;

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
