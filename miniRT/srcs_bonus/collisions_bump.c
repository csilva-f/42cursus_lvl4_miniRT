/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:01:41 by csilva-f          #+#    #+#             */
/*   Updated: 2023/11/14 22:04:09 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_vector	bump(t_vector vec, int **map, int x, int y)
{
	double		xangle;
	double		yangle;
	t_vector	tang1;
	t_vector	tang2;
	t_vector	norm;

	xangle = (vector_dot(vec, (t_vector){1, 0, 0}) + 1) * 2500;
	yangle = (vector_dot(vec, (t_vector){0, 1, 0}) + 1) * 2500;
	x = (int)xangle;
	y = (int)yangle;
	if (x != 0)
		tang1 = vector_create((t_pos){x, y, map[x][y]}, \
						(t_pos){x - 1, y, map[x - 1][y]});
	else
		tang1 = vector_create((t_pos){x, y, map[x][y]}, \
						(t_pos){x + 1, y, map[x + 1][y]});
	if (y != 0)
		tang2 = vector_create((t_pos){x, y, map[x][y]}, \
						(t_pos){x, y - 1, map[x][y - 1]});
	else
		tang2 = vector_create((t_pos){x, y, map[x][y]}, \
						(t_pos){x, y + 1, map[x][y + 1]});
	norm = vector_norm(vector_cross(tang1, tang2));
	return (vector_norm(vector_add(norm, vec)));
}

bool	sphere_collision_bump(t_sphere *sp, t_ray *r)
{
	t_vector	x;
	double		c;
	double		t;

	x = vector_create(r->p0, sp->pos);
	c = vector_dot(x, x) - sp->d_squared;
	t = quadratic_form(r->sqrt_len, vector_dot(r->v1, x) * 2, c);
	if (t > 0)
	{
		if (r->t == -1 || (t < r->t))
		{
			r->t = t;
			r->reflex_times--;
			r->color = sp->color;
			r->shine = sp->shine;
			r->norm_v = bump(vector_norm(vector_create(ray_pos(r->p0, \
							r->v1, t), sp->pos)), sp->map, 0, 0);
			return (true);
		}
	}
	return (false);
}
