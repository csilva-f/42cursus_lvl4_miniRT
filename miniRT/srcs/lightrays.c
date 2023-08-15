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

// p2(t) = (p.x, p.y, p.z) + (v.x, v.y, v.z) * t
// ter em conta que v e' vetor mas as contas e' como
// se fossem coordenadas penso?
t_pos	ray_pos(t_pos p, t_vector v, float t)
{
	return (coord_add(p, coord_mult_const(vector_to_pos(v), t)));
}

// vou usar a estrutura de codigo que tu criaste para os solidos na func luz 
// talvez seja temp, nao sei se se aplica bem para este caso

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

t_ray	*ray_last(t_ray *ray)
{
	t_ray	*aux;

	if (!ray)
		return (NULL);
	aux = ray;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	ray_add_b(t_ray **ray, t_ray *ray_new)
{
	t_ray	*aux;

	if (ray)
	{
		if (*ray)
		{
			aux = ray_last(*ray);
			aux->next = ray_new;
			ray_new = aux;
		}
		else
			*ray = ray_new;
	}
}

int	my_mlx_pixel_put(t_mini *m, int x, int y, int color)
{
	char	*dst;

	dst = m->g->addr + (y * m->g->line_length + x
			* (m->g->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

void	collisions(t_mini *m, int x, int y)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	if (m->sp)
	{
		while (m->sp)
		{
			sphere_collision(m->sp, m->ray);
			m->sp = m->sp->next;
		}
	}
	if (m->plane)
	{
		while (m->plane)
		{
			plane_collision(m->plane, m->ray);
			m->plane = m->plane->next;
		}
	}
	if (m->cyl)
	{
		while (m->cyl)
		{
			cylinder_collision(m->cyl, m->ray);
			m->cyl = m->cyl->next;
		}
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
	while (x <= m->g->width)
	{
		y = 0;
		px = (x + 0.5) / m->g->width;
		while (y <= m->g->height)
		{
			p = pixel_pos(px, (y + 0.5) / m->g->height, m);
			m->ray = ray_new(p, pixel_vec(p));
			collisions(m, x, y);
			y++;
			m->ray = m->ray->next;
		}
		printf("%i  pixelpos= %f %f %f\n", x, p.x, p.y, p.z);
		x++;
	}
	mlx_put_image_to_window(m->g->mlx, m->g->win, m->g->img, 0, 0);
	m->ray = temp;
}

/*
void	ray_create(t_mini *m)
{
	int			x;
	int			y;
	float		px;
	t_pos		p;
	t_ray		*temp;

	float	viewport_height = 2.0;
    float	viewport_width = 16 / 9 * viewport_height;
    float	focal_length = 1.0;

    t_pos or = m->cam->pos;
    t_vector horizontal = vector_new(viewport_width, 0.0, 0.0);
    t_vector vertical = vector_new(0.0, viewport_height, 0.0);
    t_pos llc = coord_sub(or, coord_new(-1 * viewport_width / 2.0, -1 * viewport_height / 2.0,
                          -1 * focal_length));

	t_vector	u;
	t_vector	v;
	t_vector	vec;

	x = 0;
	temp = m->ray;
	while (x <= m->g->width)
	{
		y = 0;
		px = (x + 0.5) / m->g->width;
		u = vector_mult_const(horizontal, (float) x / m->g->width);
		while (y <= m->g->height)
		{
			v = vector_mult_const(vertical, (float) y / m->g->height);
			p = or;
			vec = vector_sub(vector_add(vector_add(pos_to_vector(llc), u), v), pos_to_vector(or));
			m->ray = ray_new(p, vec);
			collisions(m, x, y);
			y++;
			m->ray = m->ray->next;
		}
		printf("%i  pixelvec= %f %f %f\n", x, vec.vx, vec.vy, vec.vz);
		x++;
	}
	mlx_put_image_to_window(m->g->mlx, m->g->win, m->g->img, 0, 0);
	m->ray = temp;
}*/