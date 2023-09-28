/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:02:42 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/26 15:02:44 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector	rotate_vector(t_vector orig, t_vector axis, float angle)
{
	float		rad;
	float		coss;
	float		sen;
	float		one_coss;
	t_vector	rot;

	rad = angle * PI / 180.0;
	coss = cos(rad);
	sen = sin(rad);
	one_coss = 1.0 - coss;
	rot.vx = (coss + axis.vx * axis.vx * one_coss) * orig.vx + \
		(axis.vx * axis.vy * one_coss - axis.vz * sen) * orig.vy + \
		(axis.vx * axis.vz * one_coss + axis.vy * sen) * orig.vz;
	rot.vy = (axis.vy * axis.vx * one_coss + axis.vz * sen) * orig.vx + \
		(coss + axis.vy * axis.vy * one_coss) * orig.vy + (axis.vy * \
		axis.vz * one_coss - axis.vx * sen) * orig.vz;
	rot.vz = (axis.vz * axis.vx * one_coss - axis.vy * sen) * orig.vx + \
		(axis.vz * axis.vy * one_coss + axis.vx * sen) * orig.vy + (coss - \
		axis.vz * axis.vz * one_coss) * orig.vz;
	return (vector_norm(rot));
}

t_vector	rotate_vector_x(t_vector orig, float angle)
{
	float		coss;
	float		sen;
	t_vector	rot;

	coss = cos(angle * PI / 180.0);
	sen = sin(angle * PI / 180.0);
	rot.vx = orig.vx;
	rot.vy = coss * orig.vy - sen * orig.vz;
	rot.vz = sen * orig.vy + coss * orig.vz;
	return (vector_norm(rot));
}

t_vector	rotate_vector_y(t_vector orig, float angle)
{
	float		coss;
	float		sen;
	t_vector	rot;

	coss = cos(angle * PI / 180.0);
	sen = sin(angle * PI / 180.0);
	rot.vx = coss * orig.vx + sen * orig.vz;
	rot.vy = orig.vy;
	rot.vz = coss * orig.vz - sen * orig.vx;
	return (vector_norm(rot));
}

t_vector	rotate_vector_z(t_vector orig, float angle)
{
	float		coss;
	float		sen;
	t_vector	rot;

	coss = cos(angle * PI / 180.0);
	sen = sin(angle * PI / 180.0);
	rot.vx = coss * orig.vx - sen * orig.vy;
	rot.vy = sen * orig.vx + coss * orig.vy;
	rot.vz = orig.vz;
	return (vector_norm(rot));
}

void	rotate_solids(t_mini *m, char c)
{
	t_vector	axis;

	if (c == 'x')
		axis = (t_vector){1, 0, 0};
	else if (c == 'y')
		axis = (t_vector){0, 1, 0};
	else if (c == 'z')
		axis = (t_vector){0, 0, 1};
	else
		axis = (t_vector){0, 0, 0};
	if (m->s->l == 'P' && (axis.vx != 0 || axis.vy != 0 || axis.vz != 0))
		m->s->pl->vec = rotate_vector(m->s->pl->vec, axis, 15);
	else if (m->s->l == 'C' && (axis.vx != 0 || axis.vy != 0 || axis.vz != 0))
		m->s->cyl->vec = rotate_vector(m->s->cyl->vec, axis, 15);
}
