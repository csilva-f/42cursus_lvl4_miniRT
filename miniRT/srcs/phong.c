/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:42:32 by fvieira           #+#    #+#             */
/*   Updated: 2023/09/19 22:04:53 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	light_collisions(t_mini *m)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	collisions_aux(m);
	printf("t1 = %f\n", m->ray->t);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
}

bool	shadow(t_mini *m, t_ray *r)
{
	/*printf("t0 = %f\n", m->ray->t);
	m->ray->v1 = vector_create(m->light->pos, ray_pos(r->p0, r->v1, r->t));
	m->ray->p0 = m->light->pos;
	light_collisions(m);
	if (m->ray->t < 1 && m->ray->t > 0)
	{
		m->ray = r;
		return (false);
	}
	m->ray = r;
	printf("t2 = %f\n", m->ray->t);*/
	(void)m;
	(void)r;
	return (true);
}
//para mandatory so temos uma luz por isso vou assumir isso
//depois temos de alterar no bonus pq podemos ter varias e nao deve ser dificil

t_pos	phong(t_mini *m, t_ray *r, bool diffuse)//, float alpha)
{
	t_pos		i;
	float		k_a;
	float		k_d;
	t_pos		amb;
	t_pos		diff;
	t_vector	l;
	/*float		k_s;
	t_pos		spec;*/
	k_a = m->al->ratio;
	//k_s = 1;
	k_d = m->light->ratio;
	l = vector_norm(vector_create(m->light->pos, ray_pos(r->p0, r->v1, r->t)));
	amb = multconst_rgb(k_a, r->color);
	(void)diffuse;
	//if (diffuse)
	diff = multconst_rgb(k_d * vector_dot(r->norm_v, l), r->color);
	//else
	//	diff = (t_pos){0,0,0};
	i = add_rgb(amb, diff);
	/*spec = multconstRGB(k_s, pow(vector_dot(reflected_ray(r, l), \
					vector_mult_const(vector_create(ray_pos(r->p0, \
					r->v1, r->t), coord_new(0, 0, -1)), -1)), 1);*/
	return (i);
}
