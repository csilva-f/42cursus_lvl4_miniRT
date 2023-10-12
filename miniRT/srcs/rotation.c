/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:10:03 by csilva-f          #+#    #+#             */
/*   Updated: 2023/10/12 21:40:44 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector	rotation_axis(char c)
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
	return (axis);
}

t_vector	rotation_matrix(char c, t_vector v, float angle, float *n)
{
	t_vector	u;

	n[0] = cos(angle);
	n[1] = sin(angle);
	if (c == 'x')
	{
		u.vx = v.vx;
		u.vy = v.vy * n[0] - v.vz * n[1];
		u.vz = v.vy * n[1] + v.vz * n[0];
	}
	else if (c == 'y')
	{
		u.vx = v.vx * n[0] + v.vz * n[1];
		u.vy = v.vy;
		u.vz = -v.vx * n[1] + v.vz * n[0];
	}
	else if (c == 'z')
	{
		u.vx = v.vx * n[0] - v.vy * n[1];
		u.vy = v.vy * n[1] + v.vy * n[0];
		u.vz = v.vz;
	}
	else
		u = v;
	return (u);
}

t_vector	vector_origin(t_vector v, t_pos o, int sub)
{
	t_vector	u;

	if (sub == 1)
	{
		u.vx = v.vx - o.x;
		u.vy = v.vy - o.y;
		u.vz = v.vz - o.z;
	}
	else
	{
		u.vx = v.vx + o.x;
		u.vy = v.vy + o.y;
		u.vz = v.vz + o.z;
	}
	return (u);
}

void	cam_rotation(t_mini *m, char c, float *n)
{
	t_cylinder	*t_cyl;
	t_plane		*t_pl;

	t_cyl = m->cyl;
	t_pl = m->plane;
	m->cam->vec = rotate_vector(m->cam->vec, rotation_axis(c), 15);
	while (m->cyl)
	{
		m->cyl->vec = vector_origin(m->cyl->vec, m->cam->pos, 1);
		m->cyl->vec = rotation_matrix(c, m->cyl->vec, 15.0 * PI / 180.0, n);
		m->cyl->vec = vector_norm(vector_origin(m->cyl->vec, m->cam->pos, 0));
		m->cyl = m->cyl->next;
	}
	while (m->plane)
	{
		m->plane->vec = vector_origin(m->plane->vec, m->cam->pos, 1);
		m->plane->vec = rotation_matrix(c, m->plane->vec, 15.0 * PI / 180.0, n);
		m->plane->vec = vector_norm(vector_origin(m->plane->vec, \
					m->cam->pos, 0));
		m->plane = m->plane->next;
	}
	m->cyl = t_cyl;
	m->plane = t_pl;
	data_transform(m);
	destroy_create_image(m, 0);
}
