/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:54:06 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/14 16:54:08 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coords_vectors.h"

t_pos	coord_add(t_pos c1, t_pos c2)
{
	t_pos	novo;

	novo.x = c1.x + c2.x;
	novo.y = c1.y + c2.y;
	novo.z = c1.z + c2.z;
	return (novo);
}

t_pos	coord_sub(t_pos c1, t_pos c2)
{
	t_pos	novo;

	novo.x = c1.x - c2.x;
	novo.y = c1.y - c2.y;
	novo.z = c1.z - c2.z;
	return (novo);
}

t_pos	coord_mult_const(t_pos c1, float c)
{
	t_pos	novo;

	novo.x = c1.x * c;
	novo.y = c1.y * c;
	novo.z = c1.z * c;
	return (novo);
}

float	distance(t_pos p1, t_pos p2)
{
	float	xpart;
	float	ypart;
	float	zpart;

	xpart = (p1.x - p2.x) * (p1.x - p2.x);
	ypart = (p1.y - p2.y) * (p1.y - p2.y);
	zpart = (p1.z - p2.z) * (p1.z - p2.z);
	return (sqrt(xpart + ypart + zpart));
}

t_pos	coord_new(float c1, float c2, float c3)
{
	t_pos	novo;

	novo.x = c1;
	novo.y = c2;
	novo.z = c3;
	return (novo);
}
