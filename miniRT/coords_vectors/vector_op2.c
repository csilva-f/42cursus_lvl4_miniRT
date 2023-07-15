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
