/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:02:28 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/09 20:18:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_vector	eq_transform(t_mini *m, double *angle)
{
	t_vector	final;
	t_vector	axis;

	final = (t_vector){0, 0, -1};
	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	*(angle) *= -1;
	axis = vector_cross(m->cam->vec, final);
	if (axis.vx == 0 && axis.vy == 0 && axis.vz == 0)
		axis.vy = 1;
	return (vector_norm(axis));
}

t_vector	rotate_vector_aux(double angle, t_vector axis, t_vector v)
{
	t_vector	result;
	double		coss;
	double		sen;

	axis = vector_norm(axis);
	coss = cos(angle);
	sen = sin(angle);
	angle = 0.261799;
	coss = cos(angle);
	sen = sin(angle);
	axis = vector_norm(axis);
	result.vx = v.vx * coss - v.vy * sen;
	result.vy = v.vx * sen + v.vy * coss;
	result.vz = v.vz;
	return (vector_norm(result));
}
