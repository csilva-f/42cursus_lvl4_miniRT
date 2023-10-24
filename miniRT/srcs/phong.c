/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:42:32 by fvieira           #+#    #+#             */
/*   Updated: 2023/10/12 22:24:31 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	collisions_aux2(t_mini *m, t_ray *ray)
{
	while (m->sp)
	{
		sphere_collision(m->sp, ray);
		m->sp = m->sp->next;
		if (ray->t >= 0.0005)
			return ;
	}
	while (m->plane)
	{
		plane_collision(m->plane, ray);
		m->plane = m->plane->next;
		if (ray->t >= 0.0005)
			return ;
	}
	while (m->cyl)
	{
		cylinder_collision(m->cyl, ray);
		m->cyl = m->cyl->next;
		if (ray->t >= 0.0005)
			return ;
	}
}

void	light_collisions(t_mini *m, t_ray *temp)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	collisions_aux2(m, temp);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
}

bool	shadow(t_mini *m)
{
	t_ray	*temp;
	t_pos	hit_c;

	temp = malloc(sizeof(t_ray));
	hit_c = ray_pos(m->ray->p0, m->ray->v1, m->ray->t - 0.0001);
	temp->v1 = vector_norm(vector_create(m->light->pos, hit_c));
	temp->sqrt_len = vector_dot(temp->v1, temp->v1);
	temp->p0 = hit_c;
	temp->t = -1;
	light_collisions(m, temp);
	if (temp->t < 0.0005 && temp->t >= 0)
		temp->t = -1;
	if (temp->t == -1 || distance(m->light->pos, temp->p0) \
		< distance(ray_pos(temp->p0, temp->v1, temp->t), temp->p0))
	{
		free(temp);
		return (true);
	}
	free(temp);
	return (false);
}

t_pos	phong(t_mini *m, t_ray *r, bool diffuse)
{
	t_pos		i;
	double		k[2];
	t_pos		amb;
	t_pos		diff;
	t_vector	l;

	k[0] = m->al->ratio;
	k[1] = m->light->ratio;
	l = vector_norm(vector_create(m->light->pos, ray_pos(r->p0, \
					r->v1, r->t * 0.99999)));
	amb = multconst_rgb(k[0], r->color);
	(void)diffuse;
	if (diffuse)
		diff = multconst_rgb(k[1] * vector_dot(r->norm_v, l), r->color);
	else
		diff = (t_pos){0, 0, 0};
	i = add_rgb(amb, diff);
	/*spec = multconstRGB(k_s, pow(vector_dot(reflected_ray(r, l), \
					vector_mult_const(vector_create(ray_pos(r->p0, \
					r->v1, r->t), coord_new(0, 0, -1)), -1)), 1);*/
	return (i);
}
