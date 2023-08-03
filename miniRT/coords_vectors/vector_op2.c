/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:10:12 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/15 18:10:13 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coords_vectors.h"

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	novo;

	novo.vx = v1.vy * v2.vz - v1.vz * v2.vy;
	novo.vy = v1.vz * v2.vx - v1.vx * v2.vz;
	novo.vz = v1.vx - v2.vy - v1.vy * v2.vx;
	return (novo);
}

float	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.vx * v2.vx + v1.vy * v2.vy + v1.vz * v2.vz);
}

t_pos	vector_to_pos(t_vector v1)
{
	t_pos	novo;

	novo.x = v1.vx;
	novo.y = v1.vy;
	novo.z = v1.vz;
	return (novo);
}

t_vector	pos_to_vector(t_pos p1)
{
	t_vector	novo;

	novo.vx = p1.x;
	novo.vy = p1.y;
	novo.vz = p1.z;
	return (novo);
}

t_vector	vector_norm(t_vector v)
{
	t_vector	novo;

	novo.vx = v.vx / length(v);
	novo.vy = v.vy / length(v);
	novo.vz = v.vz / length(v);
	return (novo);
}
