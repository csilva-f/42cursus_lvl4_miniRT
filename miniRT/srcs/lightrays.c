/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightrays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:45:27 by fvieira           #+#    #+#             */
/*   Updated: 2023/07/29 16:45:28 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_pos	ray_pos(t_pos p, t_vector v, float t)
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

void	collisions(t_mini *m, int x, int y)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	while (m->sp)
	{
		sphere_collision(m->sp, m->ray);
		m->sp = m->sp->next;
	}
	while (m->plane)
	{
		plane_collision(m->plane, m->ray);
		m->plane = m->plane->next;
	}
	while (m->cyl)
	{
		cylinder_collision(m->cyl, m->ray);
		m->cyl = m->cyl->next;
	}
	if (m->ray->t > -1)
		my_mlx_pixel_put(m, x, y, m->ray->color);
	else
		my_mlx_pixel_put(m, x, y, m->al->color);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
}

void	ray_create(t_mini *m)
{
	int			x;
	int			y;
	float		px;
	t_pos		p;
	t_ray		*temp;

	x = 0;
	temp = m->ray;
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
			//m->ray = m->ray->next;
		}
		//printf("%i  pixelpos= %f %f %f\n", x, p.x, p.y, p.z);
		x++;
	}
	mlx_put_image_to_window(m->g->mlx, m->g->win, m->g->img, 0, 0);
	m->ray = temp;
}
