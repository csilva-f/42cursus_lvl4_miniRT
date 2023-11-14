/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:42:32 by fvieira           #+#    #+#             */
/*   Updated: 2023/11/12 13:28:29 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"
#include <math.h>
#include <stdio.h>

void	collisions_aux3(t_mini *m, t_ray *ray)
{
	while (m->co)
	{
		cone_collision(m->co, ray);
		m->co = m->co->next;
		if (ray->t >= 0.0005)
			return ;
	}
}

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
		plane_collision(m->plane, ray, 0, 0);
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
	collisions_aux3(m, ray);
}

void	light_collisions(t_mini *m, t_ray *temp)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	t_cylinder	*temp_cyl;
	t_cone		*temp_co;

	temp_pl = m->plane;
	temp_sp = m->sp;
	temp_cyl = m->cyl;
	temp_co = m->co;
	collisions_aux2(m, temp);
	m->plane = temp_pl;
	m->sp = temp_sp;
	m->cyl = temp_cyl;
	m->co = temp_co;
}

bool	shadow(t_mini *m, t_light *l)
{
	t_ray	*temp;
	t_pos	hit_c;

	temp = malloc(sizeof(t_ray));
	hit_c = ray_pos(m->ray->p0, m->ray->v1, m->ray->t - 0.0001);
	temp->v1 = vector_norm(vector_create(l->pos, hit_c));
	temp->sqrt_len = vector_dot(temp->v1, temp->v1);
	temp->p0 = hit_c;
	temp->t = -1;
	light_collisions(m, temp);
	if (temp->t < 0.0005 && temp->t >= 0)
		temp->t = -1;
	if (temp->t == -1 || distance(l->pos, temp->p0) \
		< distance(ray_pos(temp->p0, temp->v1, temp->t), temp->p0))
	{
		free(temp);
		return (true);
	}
	free(temp);
	return (false);
}

double	vec_cos(t_vector v1, t_vector v2)
{
	double	dot;
	double	lengths;

	dot = vector_dot(v1, v2);
	lengths = length(v1) * length(v2);
	return (dot / lengths);
}

t_pos	phong(t_mini *m, t_ray *r)
{
	t_pos		i;
	t_pos		k[2];
	t_pos		amb;
	t_pos		diff;
	t_vector	l;
	t_light		*aux_l;
	double 		dot;
	t_pos		spec;

	aux_l = m->light;
	k[0] = multconst_rgb(m->al->ratio, m->al->color);
	i = (t_pos){0, 0, 0};
	amb = multiply_rgb(k[0], r->color);
	while (aux_l != NULL)
	{
		k[1] = multconst_rgb(aux_l->ratio, aux_l->color);
		l = vector_norm(vector_create(aux_l->pos, ray_pos(r->p0, \
						r->v1, r->t * 0.99999)));
		dot = vector_dot(r->norm_v, l);
		//printf("dot %f\n", dot);
		if (dot > 0 && shadow(m, aux_l))
		{
			diff = multiply_rgb(multconst_rgb(dot, k[1]), r->color);
			spec = mix_rgb(multiply_rgb(multconst_rgb(0.8 * pow(vector_dot(\
				vector_norm(vector_add(vector_norm(\
				vector_mult_const(r->v1, -1)), l)), r->norm_v), r->shine), \
				k[1]), r->color), aux_l->color);
			//printf("sol %f %f %f ", diff.x, diff.y, diff.z);
			//printf("| %f %f %f \n", spec.x, spec.y, spec.z);

		}
		else
		{
			//printf("sombra %f %f %f\n", amb.x, amb.y, amb.z);
			diff = (t_pos){0, 0, 0};
			spec = (t_pos){0, 0, 0};
		}
		i = add_rgb(add_rgb(i, add_rgb(amb, diff)), spec);
		aux_l = aux_l->next;
	}
	return (i);
}

//i = add_rgb(i, add_rgb(amb, diff));
		/*spec = multconst_rgb(0.8, pow(vector_dot(reflected_ray(r, l), \
					vector_mult_const(vector_create(ray_pos(r->p0, \
					r->v1, r->t), coord_new(0, 0, -1)), -1)), 1));*/
