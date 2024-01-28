/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:15:41 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/15 15:15:42 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coords_vectors.h"

double	length(t_vector v1)
{
	return (sqrt(v1.vx * v1.vx + v1.vy * v1.vy + v1.vz * v1.vz));
}

t_vector	vector_mult_const(t_vector v1, double c)
{
	t_vector	novo;

	novo.vx = v1.vx * c;
	novo.vy = v1.vy * c;
	novo.vz = v1.vz * c;
	return (novo);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	novo;

	novo.vx = v1.vx + v2.vx;
	novo.vy = v1.vy + v2.vy;
	novo.vz = v1.vz + v2.vz;
	return (novo);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	novo;

	novo.vx = v1.vx - v2.vx;
	novo.vy = v1.vy - v2.vy;
	novo.vz = v1.vz - v2.vz;
	return (novo);
}

t_vector	vector_create(t_pos p1, t_pos p2)
{
	t_vector	novo;

	novo.vx = p1.x - p2.x;
	novo.vy = p1.y - p2.y;
	novo.vz = p1.z - p2.z;
	return (novo);
}
