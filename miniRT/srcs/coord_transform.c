/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:39:09 by fvieira           #+#    #+#             */
/*   Updated: 2023/10/09 21:21:27 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
	return (result);
}

t_vector	eq_transform(t_mini *m, float *angle)
{
	t_vector	final;
	t_vector	axis;

	final = (t_vector){0, 0, -1};
	//m->cam->vec = vector_norm((t_vector){0, 0, -1});
	*(angle) = acos(vector_dot(m->cam->vec, final) / length(m->cam->vec));
	axis = vector_cross(m->cam->vec, final);
	return (axis);
}

float	scalar_calc(t_pos pos, t_vector vec)
{
	if (pos.x && vec.vx)
		return (pos.x / vec.vx);
	else if (pos.y && vec.vy)
		return (pos.y / vec.vy);
	else if (pos.z && vec.vz)
		return (pos.z / vec.vz);
	else
		return (0);
}

void	data_transform_aux(t_mini *m)
{
	float		angle;
	float		temp;
	t_vector	axis_of_rot;

	axis_of_rot = eq_transform(m, &angle);
	angle *= -1;
	printf("angle %f\n", angle);
	while (m->sp)
	{
		m->sp->pos = coord_sub(m->sp->pos, m->cam->pos);
		printf("pos %f %f %f\n", m->sp->pos.x, m->sp->pos.y, m->sp->pos.z);
		m->sp->orig = vector_norm(vector_create(m->sp->pos, (t_pos){0, 0, 0}));
		m->sp->orig = rotate_vector_2(m->sp->orig, axis_of_rot, angle);
		temp = scalar_calc(m->sp->pos, m->sp->orig);
		m->sp->pos = ray_pos((t_pos){0, 0, 0}, m->sp->orig, temp);
		printf("pos %f %f %f\n", m->sp->pos.x, m->sp->pos.y, m->sp->pos.z);
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		m->plane->pos = coord_sub(m->plane->pos, m->cam->pos);
		m->plane->orig = vector_norm(vector_create(m->plane->pos, (t_pos) {0, 0, 0}));
		m->plane->orig = rotate_vector_2(m->plane->orig, axis_of_rot, angle);
		temp = scalar_calc(m->plane->pos, m->plane->orig);
		m->plane->pos = ray_pos((t_pos){0, 0, 0}, m->plane->orig, temp);
		m->plane->vec = rotate_vector_2(m->plane->vec, m->plane->orig, angle);
		m->plane = m->plane->next;
	}
	while (m->cyl)
	{
		m->cyl->pos = coord_sub(m->cyl->pos, m->cam->pos);
		m->cyl->orig = vector_norm(vector_create(m->cyl->pos, (t_pos) {0, 0, 0}));
		m->cyl->orig = rotate_vector_2(m->cyl->orig, axis_of_rot, angle);
		temp = scalar_calc(m->cyl->pos, m->cyl->orig);
		m->cyl->pos = ray_pos((t_pos){0, 0, 0}, m->cyl->orig, temp);
		m->cyl->vec = rotate_vector_2(m->cyl->vec, m->cyl->orig, angle);
		m->cyl = m->cyl->next;
	}
	while (m->light)
	{
		m->light->pos = coord_sub(m->light->pos, m->cam->pos);
		m->light->orig = vector_norm(vector_create(m->light->pos, (t_pos) {0, 0, 0}));
		m->light->orig = rotate_vector_2(m->light->orig, axis_of_rot, angle);
		temp = scalar_calc(m->light->pos, m->light->orig);
		m->light->pos = ray_pos((t_pos){0, 0, 0}, m->light->orig, temp);
		m->light = m->light->next;
	}
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
	//m->cam->pos.z -= 1;
	data_transform_aux(m);
	m->sp = temp_sp;
	m->plane = temp_pl;
	m->cyl = temp_cyl;
	m->light = temp_light;
	m->cam->pos = (t_pos){0, 0, 0};
	m->cam->vec = (t_vector){0, 0, -1};
}

/*
void	data_transform(t_mini *mini)
{
	coord_transform(mini);
	eq_transform(mini);
}*/
