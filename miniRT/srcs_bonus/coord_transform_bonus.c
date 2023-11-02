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

t_vector	rotate_vector_2(t_mini *m, t_vector v, t_vector axis, double angle)
{
	t_vector	result;
	double		coss;
	double		sen;

	axis = vector_norm(axis);
	coss = cos(angle);
	sen = sin(angle);
	if (angle == 0 && m->flag == false)
		return (rotate_vector_aux(angle, axis, v));
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

void	data_transform_aux_2(t_mini *m, double angle, t_vector axis, t_pos o)
{
	while (m->cyl)
	{
		m->cyl->pos = coord_sub(m->cyl->pos, m->cam->pos);
		m->cyl->orig = vector_norm(vector_create(m->cyl->pos, o));
		m->cyl->orig = rotate_vector_2(m, m->cyl->orig, axis, angle);
		m->cyl->pos = ray_pos(o, m->cyl->orig, distance(m->cyl->pos, o));
		if (m->cam->vec.vy && m->init)
			m->cyl->vec = vector_norm(rotation_matrix('x', m->cyl->vec, \
						PI / 2, (double [2]){0}));
		if (m->cam->vec.vx && m->init)
			m->cyl->vec = vector_norm(rotation_matrix('y', m->cyl->vec, \
						PI / 2, (double [2]){0}));
		m->cyl = m->cyl->next;
	}
	while (m->co)
	{
		m->co->pos = coord_sub(m->co->pos, m->cam->pos);
		m->co->orig = vector_norm(vector_create(m->co->pos, o));
		m->co->orig = rotate_vector_2(m, m->co->orig, axis, angle);
		m->co->pos = ray_pos(o, m->co->orig, distance(m->co->pos, o));
		if (m->cam->vec.vy && m->init)
			m->co->vec = vector_norm(rotation_matrix('x', m->co->vec, \
						PI / 2, (double [2]){0}));
		if (m->cam->vec.vx && m->init)
			m->co->vec = vector_norm(rotation_matrix('y', m->co->vec, \
						PI / 2, (double [2]){0}));
		m->co = m->co->next;
	}
	while (m->light)
	{
		m->light->pos = coord_sub(m->light->pos, m->cam->pos);
		m->light->orig = vector_norm(vector_create(m->light->pos, o));
		m->light->orig = rotate_vector_2(m, m->light->orig, axis, angle);
		m->light->pos = ray_pos(o, m->light->orig, distance(m->light->pos, o));
		m->light = m->light->next;
	}
}

void	data_transform_aux(t_mini *m, double a, t_pos o, t_vector axis_of_rot)
{
	axis_of_rot = eq_transform(m, &a);
	while (m->sp)
	{
		m->sp->pos = coord_sub(m->sp->pos, m->cam->pos);
		m->sp->orig = vector_norm(vector_create(m->sp->pos, o));
		m->sp->orig = rotate_vector_2(m, m->sp->orig, axis_of_rot, a);
		m->sp->pos = ray_pos(o, m->sp->orig, distance(m->sp->pos, o));
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		m->plane->pos = coord_sub(m->plane->pos, m->cam->pos);
		m->plane->orig = vector_norm(vector_create(m->plane->pos, o));
		m->plane->orig = rotate_vector_2(m, m->plane->orig, axis_of_rot, a);
		if (m->cam->vec.vy && m->init)
			m->plane->vec = vector_norm(rotation_matrix('x', m->plane->vec, \
						PI / 2, (double [2]){0}));
		if (m->cam->vec.vx && m->init)
			m->plane->vec = vector_norm(rotation_matrix('y', m->plane->vec, \
						PI / 2, (double [2]){0}));
		m->plane->pos = ray_pos(o, m->plane->orig, distance(m->plane->pos, o));
		m->plane = m->plane->next;
	}
	data_transform_aux_2(m, a, axis_of_rot, o);
}

void	data_transform(t_mini *m)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;
	t_cone		*temp_co;
	t_light		*temp_light;

	temp_sp = m->sp;
	temp_pl = m->plane;
	temp_cyl = m->cyl;
	temp_co = m->co;
	temp_light = m->light;
	data_transform_aux(m, 0.0, (t_pos){0, 0, 0}, (t_vector){0, 0, 0});
	m->sp = temp_sp;
	m->plane = temp_pl;
	m->cyl = temp_cyl;
	m->co = temp_co;
	m->light = temp_light;
	m->cam->pos = (t_pos){0, 0, 0};
	m->cam->vec = (t_vector){0, 0, -1};
}

/*t_vector	eq_transform2(t_mini *m, double *angle)
{
	t_vector	final;
	t_vector	axis;

	final = (t_vector){0, -1, 0};
	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	*(angle) *= -1;
	axis = vector_cross(m->cam->vec, final);
	if (axis.vx == 0 && axis.vy == 0 && axis.vz == 0)
		axis.vz = 1;
	return (axis);
}

t_vector	eq_transform3(t_mini *m, double *angle, t_vector final)
{
	t_vector	axis;

	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	*(angle) *= -1;
	axis = vector_cross(m->cam->vec, final);
	if (axis.vx == 0 && axis.vy == 0 && axis.vz == 0)
		axis.vz = 1;
	return (axis);
}

t_vector	rot_matrix_axis2(t_mini *m, t_vector v)
{
	t_vector	u;
	double	angle;

	eq_transform3(m, &angle, (t_vector) {1, 0, 0});
	u = rotation_matrix('x', v, angle, (double [2]){0});
	eq_transform3(m, &angle, (t_vector) {0, 1, 0});
	u = rotation_matrix('y', v, angle, (double [2]){0});
	eq_transform3(m, &angle, (t_vector) {0, 0, 1});
	u = rotation_matrix('z', v, angle, (double [2]){0});
	return (u);
}

t_vector	rot_matrix_axis(double angle, t_vector a, t_vector v)
{
	double		s;
	double		c;
	double		m[9];
	t_vector	u;

	s = sin(angle);
	c = 1 - cos(angle);
	m[0] = 1 + c * (-1 * pow(a.vz, 2) - pow(a.vy, 2));
	m[1] = -1 * a.vz * s + c * a.vx * a.vy;
	m[2] = a.vy * s - c * a.vz * a.vx;
	m[3] = a.vz * s + c * a.vx * a.vy;
	m[4] = 1 + c * (-1 * pow(a.vx, 2) - pow(a.vz, 2));
	m[5] = -1 * a.vx * s + c * a.vz * a.vy;
	m[6] = -1 * a.vy * s - c * a.vz * a.vy;
	m[7] = a.vx * s + c * a.vz * a.vx;
	m[8] = 1 + c * (-1 * pow(a.vx, 2) - pow(a.vy, 2));
	u.vx = m[0] * v.vx + m[1] * v.vy + m[2] * v.vz;
	u.vy = m[3] * v.vx + m[4] * v.vy + m[5] * v.vz;
	u.vz = m[6] * v.vx + m[7] * v.vy + m[8] * v.vz;
	return (u);
}

t_vector	rotation(t_vector v1)
{
	double		angle;
	char		c;
	t_vector	u;

	u = v1;
	if (v1.vx)
	{
		angle = -PI / 2;
		c = 'z';
		u = rotation_matrix(c, v1, angle, (double [2]){0});
	}
	else if (v1.vz)
	{
		angle = PI / 2;
		c = 'x';
		u = rotation_matrix(c, v1, angle, (double [2]){0});
	}
	return (vector_norm(u));
}*/
