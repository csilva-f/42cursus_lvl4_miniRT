/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:20:42 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/07 23:21:32 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	cam_rotation_aux3(t_mini *m, char c, double *n)
{
	m->co->vec = vector_origin(m->co->vec, m->cam->pos, 1);
	m->co->vec = rotation_matrix(c, m->co->vec, 5.0 * PI / 60.0, n);
	m->co->vec = vector_norm(m->co->vec);
	m->co->vec = vector_norm(vector_origin(m->co->vec, m->cam->pos, 0));
	m->co = m->co->next;
}

void	cam_rotation(t_mini *m, char c, double *n)
{
	t_cylinder	*t_cyl;
	t_plane		*t_pl;
	t_cone		*t_co;

	t_cyl = m->cyl;
	t_pl = m->plane;
	t_co = m->co;
	m->cam->vec = rotate_vector(m->cam->vec, rotation_axis(c), 15);
	while (m->cyl)
		cam_rotation_aux(m, c, n);
	while (m->plane)
		cam_rotation_aux2(m, c, n);
	while (m->co)
		cam_rotation_aux3(m, c, n);
	m->cyl = t_cyl;
	m->co = t_co;
	m->plane = t_pl;
	m->flag = false;
	data_transform(m);
	destroy_create_image(m, 0);
}

/*t_vector	orientation(t_mini *mini, t_vector v)
{
	t_vector	r;
	t_vector	u;
	t_vector	d;
	t_vector	w;

	d = vector_mult_const(mini->cam->vec, -1);
	r = vector_norm(vector_cross((t_vector){0, 1, 0}, d));
	u = vector_norm(vector_cross(d, r));
	w.vx = v.vx * r.vx + v.vy * r.vy + v.vz * r.vz;
	w.vy = v.vx * u.vx + v.vy * u.vy + v.vz * u.vz;
	w.vz = v.vx * d.vx + v.vy * d.vy + v.vz * d.vz;
	return (vector_norm(w));
}*/
