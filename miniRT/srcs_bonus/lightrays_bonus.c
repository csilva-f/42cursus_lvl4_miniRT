/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightrays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:45:27 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/26 16:48:42 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_pos	ray_pos(t_pos p, t_vector v, double t)
{
	return (coord_add(p, coord_mult_const(vector_to_pos(v), t)));
}

t_ray	*ray_new(t_pos p, t_vector v)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->p0.x = p.x;
	ray->p0.y = p.y;
	ray->p0.z = p.z;
	ray->v1.vx = v.vx;
	ray->v1.vy = v.vy;
	ray->v1.vz = v.vz;
	ray->t = -1;
	ray->sqrt_len = vector_dot(ray->v1, ray->v1);
	ray->reflex_times = 15;
	ray->next = NULL;
	return (ray);
}

void	collisions_aux(t_mini *m, t_ray *ray)
{
	while (m->cyl)
	{
		cylinder_collision(m->cyl, ray);
		m->cyl = m->cyl->next;
	}
	while (m->co)
	{
		cone_collision(m->co, ray, NULL, (t_vector){0, 0, 0});
		m->co = m->co->next;
	}
	while (m->sp)
	{
		if (m->sp->b1 || m->sp->b2)
			sphere_collision_bump(m->sp, ray);
		else
			sphere_collision(m->sp, ray);
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		plane_collision(m->plane, ray, 0, 0);
		m->plane = m->plane->next;
	}
}

void	collisions(t_mini *m, int x, int y)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;
	t_cone		*temp_co;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	temp_co = m->co;
	collisions_aux(m, m->ray);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
	m->co = temp_co;
	if (m->ray->t > 0)
		my_mlx_pixel_put(m, x, y, phong(m, m->ray));
	else
		my_mlx_pixel_put(m, x, y, (t_pos){0, 0, 0});
}

void	ray_create(t_mini *m)
{
	int			x;
	int			y;
	double		px;
	t_pos		p;

	x = 0;
	while (x < m->g->width)
	{
		y = 0;
		px = (x + 0.5) / m->g->width;
		while (y < m->g->height)
		{
			p = pixel_pos(px, (y + 0.5) / m->g->height, m);
			m->ray = ray_new(p, pixel_vec(p));
			collisions(m, x, y);
			free(m->ray);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(m->g->mlx, m->g->win, m->g->img, 0, 0);
}
