/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:10:03 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/07 23:22:07 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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

t_vector	rotation_matrix(char c, t_vector v, double angle, double *n)
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
		u.vy = v.vx * n[1] + v.vy * n[0];
		u.vz = v.vz;
	}
	else
		u = v;
	return (vector_norm(u));
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

void	cam_rotation_aux(t_mini *m, char c, double *n)
{
	m->cyl->vec = vector_origin(m->cyl->vec, m->cam->pos, 1);
	m->cyl->vec = rotation_matrix(c, m->cyl->vec, 5.0 * PI / 60.0, n);
	m->cyl->vec = vector_norm(m->cyl->vec);
	m->cyl->vec = vector_norm(vector_origin(m->cyl->vec, m->cam->pos, 0));
	m->cyl = m->cyl->next;
}

void	cam_rotation_aux2(t_mini *m, char c, double *n)
{
	m->plane->vec = vector_origin(m->plane->vec, m->cam->pos, 1);
	m->plane->vec = rotation_matrix(c, m->plane->vec, 5.0 * PI / 60.0, n);
	m->plane->vec = vector_norm(vector_origin(m->plane->vec, \
				m->cam->pos, 0));
	m->plane = m->plane->next;
}
