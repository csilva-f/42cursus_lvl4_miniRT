/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:39:09 by fvieira           #+#    #+#             */
/*   Updated: 2023/10/12 22:08:02 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_vector	rotate_vector_2(t_vector v, t_vector axis, float angle)
{
	t_vector	result;
	float		coss;
	float		sen;

	axis = vector_norm(axis);
	coss = cos(angle);
	sen = sin(angle);
	if (angle == 0)
	{
		result.vx = v.vx;
		result.vy = v.vy;
		result.vz = v.vz;
		return (result);
	}
	result.vx = (coss + (1 - coss) * axis.vx * axis.vx) * v.vx + \
		((1 - coss) * axis.vx * axis.vy - axis.vz * sen) * v.vy + \
		((1 - coss) * axis.vx * axis.vz + axis.vy * sen) * v.vz;
	result.vy = ((1 - coss) * axis.vx * axis.vy + axis.vz * sen) * v.vx + \
		(coss + (1 - coss) * axis.vy * axis.vy) * v.vy + \
		((1 - coss) * axis.vy * axis.vz - axis.vx * sen) * v.vz;
	result.vz = ((1 - coss) * axis.vx * axis.vz - axis.vy * sen) * v.vx + \
		((1 - coss) * axis.vy * axis.vz + axis.vx * sen) * v.vy + \
		(coss + (1 - coss) * axis.vz * axis.vz) * v.vz;
	return (vector_norm(result));
}

t_vector	eq_transform(t_mini *m, float *angle)
{
	t_vector	final;
	t_vector	axis;

	final = (t_vector){0, 0, -1};
	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	*(angle) *= -1;
	axis = vector_cross(m->cam->vec, final);
	return (axis);
}

void	data_transform_aux_2(t_mini *m, float angle, t_vector axis, t_pos o)
{
	while (m->cyl)
	{
		m->cyl->pos = coord_sub(m->cyl->pos, m->cam->pos);
		m->cyl->orig = vector_norm(vector_create(m->cyl->pos, o));
		m->cyl->orig = rotate_vector_2(m->cyl->orig, axis, angle);
		m->cyl->pos = ray_pos(o, m->cyl->orig, distance(m->cyl->pos, o));
		m->cyl = m->cyl->next;
	}
	while (m->light)
	{
		m->light->pos = coord_sub(m->light->pos, m->cam->pos);
		m->light->orig = vector_norm(vector_create(m->light->pos, o));
		m->light->orig = rotate_vector_2(m->light->orig, axis, angle);
		m->light->pos = ray_pos(o, m->light->orig, distance(m->light->pos, o));
		m->light = m->light->next;
	}
}

void	data_transform_aux(t_mini *m)
{
	float		angle;
	t_vector	axis_of_rot;
	t_pos		o;

	axis_of_rot = eq_transform(m, &angle);
	o = (t_pos){0, 0, 0};
	while (m->sp)
	{
		m->sp->pos = coord_sub(m->sp->pos, m->cam->pos);
		m->sp->orig = vector_norm(vector_create(m->sp->pos, o));
		m->sp->orig = rotate_vector_2(m->sp->orig, axis_of_rot, angle);
		m->sp->pos = ray_pos(o, m->sp->orig, distance(m->sp->pos, o));
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		m->plane->pos = coord_sub(m->plane->pos, m->cam->pos);
		m->plane->orig = vector_norm(vector_create(m->plane->pos, o));
		m->plane->orig = rotate_vector_2(m->plane->orig, axis_of_rot, angle);
		m->plane->pos = ray_pos(o, m->plane->orig, distance(m->plane->pos, o));
		m->plane = m->plane->next;
	}
	data_transform_aux_2(m, angle, axis_of_rot, o);
}

void	data_transform(t_mini *m)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;
	t_light		*temp_light;

	temp_sp = m->sp;
	temp_pl = m->plane;
	temp_cyl = m->cyl;
	temp_light = m->light;
	data_transform_aux(m);
	m->sp = temp_sp;
	m->plane = temp_pl;
	m->cyl = temp_cyl;
	m->light = temp_light;
	m->cam->pos = (t_pos){0, 0, 0};
	m->cam->vec = (t_vector){0, 0, -1};
}
